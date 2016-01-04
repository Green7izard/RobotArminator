#include "stdafx.h"
#include "TableFinder.hpp"


namespace Vision {

    using namespace RobotArminator;

    TableFinder::TableFinder(Orientation orientation, Camera* cam, double tableLength, double tableWidth, bool forceSend) : IComputerVision(orientation), camera(cam), shouldAlwaysSend(forceSend), tableWidth(tableWidth), tableLength(tableLength)
    {
        //calibrate();
        //tabel = detectTable();
    }

    void TableFinder::setForceSend(bool shouldSend)
    {
        shouldAlwaysSend = shouldSend;
    }


    TableFinder::~TableFinder() {
    }

    void TableFinder::run() {
        Position2D position;
        Time time;
        while (isRunning())
        {
            time = Clock::universal_time();
            if (camera->getCurrentImage(cameraFrame))
            {
                if (locateObject(cameraFrame, position))
                {
                    VisionPosition visionPosition = convertToCoordinate(position, time);
                    if (shouldAlwaysSend || isValidPosition(&visionPosition))
                    {
                        notify(visionPosition);
                        //std::cout << "Found frame: " << visionPosition.X << "," << visionPosition.Y << "\t" << visionPosition.orientation << std::endl;
                    }
                }
            }
        }
    }

    Table TableFinder::detectTable()
    {
        //TODO
        return Table();
    }

    VisionPosition TableFinder::convertToCoordinate(Position2D &position, Time time)
    {
        double X = static_cast<double>(position.X);
        double Y = static_cast<double>(position.Y);
        //Whether the X axis is inverted
        bool xShouldBeInverted = (tabel.TopLeft.X < tabel.TopRight.X);

        double totalXLen;

        Position2D anchor;
        Position2D opposite;

        if (xShouldBeInverted)
        {
            anchor = tabel.BotRight;
            opposite = tabel.TopLeft;
            totalXLen = static_cast<double>(std::abs(anchor.X - opposite.X));
            X = (anchor.X - X)*(tableLength / totalXLen);
        }
        else
        {
            anchor = tabel.TopRight;
            opposite = tabel.BotLeft;
            totalXLen = static_cast<double>(std::abs(anchor.X - opposite.X));
            X = (X - anchor.X)*(tableLength / totalXLen);
        }
        //std::fabsf(X) for always getting the positive
        if (orientation == TOP)
        {
            double totalYLen = static_cast<double>(std::abs(anchor.Y - opposite.Y));
            if (xShouldBeInverted)
            {
                Y = (anchor.Y - Y)*(tableWidth / totalYLen);
            }
            else
            {
                Y = (Y - anchor.Y)*(tableWidth / totalYLen);
            }

        }
        else
        {
            Y = ((anchor.Y - Y) / totalXLen)*tableLength;
        }
        return VisionPosition(X, Y, time, orientation);
    }

    void TableFinder::updateImageSize(int X, int Y)
    {
        camera->setSize(X, Y);
        calibrate();
        //tabel = detectTable();
    }

    void TableFinder::mouseClick(int event, int x, int y, int flags, void *userdata)
    {
        BigTable * big = static_cast<BigTable *>(userdata);
        if (big != nullptr)
        {
            Table * table = big->table;
            Orientation orientation = big->orientation;
            if (event == cv::EVENT_LBUTTONDOWN && table != nullptr)
            {
                if (!validPoint(&table->TopLeft))
                {
                    table->TopLeft.X = x;
                    table->TopLeft.Y = y;
                    if (orientation == SIDE)
                    {
                        table->BotLeft.X = x;
                        table->BotLeft.Y = y;
                        cout << "Robot Edge set to: " << x << "," << y << endl;
                        cout << "Click the opposing side next! " << endl;
                    }
                    else
                    {
                        cout << "Top on Robot Side set to: " << x << "," << y << endl;
                        cout << "Click the Lower Robot side next! " << endl;
                    }
                }
                else if (!validPoint(&table->BotLeft) && orientation == TOP)
                {
                    table->BotLeft.X = x;
                    table->BotLeft.Y = y;

                    cout << "Bot on Robot Side set to: " << x << "," << y << endl;
                    cout << "Click the opposing upper corner next! " << endl;
                }
                else if (!validPoint(&table->TopRight))
                {
                    table->TopRight.X = x;
                    table->TopRight.Y = y;
                    if (orientation == SIDE)
                    {
                        table->BotRight.X = x;
                        table->BotRight.Y = y;
                        cout << "Opposing Edge set to: " << x << "," << y << endl;
                        cout << "Press esc to finish setting the table. " << endl;
                        cout << "Press right mouse button te remove. " << endl;
                    }
                    else
                    {
                        cout << "Top on Opposing Side set to: " << x << "," << y << endl;
                        cout << "Click the Lower Opposing side next! " << endl;
                    }
                }
                else if (!validPoint(&table->BotRight) && orientation == TOP)
                {
                    table->BotRight.X = x;
                    table->BotRight.Y = y;

                    cout << "Bot on opposing Side set to: " << x << "," << y << endl;
                    cout << "Press esc to finish setting the table. " << endl;
                    cout << "Press right mouse button te remove. " << endl;
                }
                else
                {
                    cout << "No Points left to set!" << endl;
                    cout << "Press esc to finish setting the table. " << endl;
                    cout << "Press right mouse button te remove. " << endl;
                }
            }
            else if (event == cv::EVENT_RBUTTONDOWN && table != nullptr)
            {
                if (validPoint(&table->BotRight) && orientation == TOP)
                {
                    table->BotRight.X = -1;
                    table->BotRight.Y = -1;
                    cout << "Bot on opposing Side removed, Reset it!" << endl;
                }
                else if (validPoint(&table->TopRight))
                {
                    table->TopRight.X = -1;
                    table->TopRight.Y = -1;
                    if (orientation == SIDE)
                    {
                        table->BotRight.X = -1;
                        table->BotRight.Y = -1;
                    }
                    cout << "Top on opposing Side removed, Reset it!" << endl;
                }
                else if (validPoint(&table->BotLeft) && orientation == TOP)
                {
                    table->BotLeft.X = -1;
                    table->BotLeft.Y = -1;
                    cout << "Bot on Robot Side removed, Reset it!" << endl;
                }
                else if (validPoint(&table->TopLeft))
                {
                    table->TopLeft.X = -1;
                    table->TopLeft.Y = -1;
                    if (orientation == SIDE)
                    {
                        table->BotLeft.X = -1;
                        table->BotLeft.Y = -1;
                    }
                    cout << "Top on Robot Side removed, Reset it!" << endl;
                }
                else {
                    cout << "No valid Points, please click the top on the robot side" << endl;
                }


            }
        }
    }

    bool TableFinder::validTable(Table * table)
    {
        return validPoint(&table->TopLeft) && validPoint(&table->TopRight) && validPoint(&table->BotLeft) && validPoint(&table->BotRight);
    }

    bool TableFinder::validPoint(Position2D * point)
    {
        return point->X >= 0 && point->Y >= 0;
    }

    void TableFinder::calibrate()
    {
        BigTable big;
        big.table = &tabel;
        big.orientation = orientation;
        std::string name;
        if (orientation == TOP)
        {
            name = "TableFinder: " + std::to_string(camera->getCameraNumber()) + " | TOP";
        }
        else if (orientation == SIDE)
        {
            name = "TableFinder: " + std::to_string(camera->getCameraNumber()) + " | SIDE";
        }
        std::cout << "Starting calibrating: " << name << endl;

        cv::Mat cameraFrame;
        cv::namedWindow(name, cv::WINDOW_AUTOSIZE);

        cv::setMouseCallback(name, &Vision::TableFinder::mouseClick, &big);
        while (cv::waitKey(33) != static_cast<char>(27) || !validTable(&tabel)) {
            if (camera->getCurrentImage(cameraFrame))
            {
                if (validPoint(&tabel.TopLeft))
                {
                    cv::circle(cameraFrame, cv::Point(tabel.TopLeft.X, tabel.TopLeft.Y), 15, cv::Scalar(255, 80, 80), -1);
                    cv::putText(cameraFrame, "Robot Top", cv::Point(tabel.TopLeft.X, tabel.TopLeft.Y - 15), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(80, 140, 255));
                }
                if (validPoint(&tabel.BotLeft) && orientation == TOP)
                {
                    cv::circle(cameraFrame, cv::Point(tabel.BotLeft.X, tabel.BotLeft.Y), 15, cv::Scalar(255, 80, 80), -1);
                    cv::putText(cameraFrame, "Robot Bot", cv::Point(tabel.BotLeft.X, tabel.BotLeft.Y - 15), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(80, 140, 255));
                }
                if (validPoint(&tabel.TopRight))
                {
                    cv::circle(cameraFrame, cv::Point(tabel.TopRight.X, tabel.TopRight.Y), 15, cv::Scalar(80, 255, 80), -1);
                    cv::putText(cameraFrame, "Opposing Top", cv::Point(tabel.TopRight.X, tabel.TopRight.Y - 15), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(80, 140, 255));
                }
                if (validPoint(&tabel.BotRight) && orientation == TOP)
                {
                    cv::circle(cameraFrame, cv::Point(tabel.BotRight.X, tabel.BotRight.Y), 15, cv::Scalar(80, 255, 80), -1);
                    cv::putText(cameraFrame, "Opposing Bot", cv::Point(tabel.BotRight.X, tabel.BotRight.Y - 15), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(80, 140, 255));
                }
                cv::imshow(name, cameraFrame);
            }
        }
        cv::destroyWindow(name);
    }

    void TableFinder::updateTableSize(double width, double length)
    {
        tableWidth = width;
        tableLength = length;
    }

    bool TableFinder::isValidPosition(VisionPosition * position)
    {

        if (position->X <= tableLength && position->X >= 0)
        {

            if (orientation == SIDE && position->Y >= 0)
            {
                return true;
            }
            else if (position->Y >= 0 && position->Y <= tableWidth)
            {
                return true;
            }
        }
        return false;
    }

    cv::Mat * TableFinder::getCurrentScreen()
    {
        return &cameraFrame;
    }

}
