#include "TableFinder.hpp"

namespace ComputerVision {


    TableFinder::TableFinder(Orientation orientation) : IComputerVision(orientation)
    {
        tabel = detectTable();
    }


    TableFinder::~TableFinder()
    {
    }

    Table TableFinder::detectTable() 
    {
        //TODO
        return Table();
    }

}