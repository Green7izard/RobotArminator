#pragma once
#include "IComputerVision.hpp"
#include "Table.hpp"

namespace ComputerVision
{
    class TableFinder :
        public IComputerVision
    {
    private:
        VisionPosition position;
        Table tabel;

    public:
        TableFinder(Orientation orientation);
        virtual ~TableFinder();
        Table detectTable();
    };
}

