#include <iostream>
#include "hellow.h"
#include <boost/asio.hpp>
#include <libxl.h>

int main() {
    std::cout << "Hello World!\n";
    hello();

    using namespace libxl;
    Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
    if(book)
    {
        Sheet* sheet = book->addSheet("Sheet1");
        if(sheet)
        {
            sheet->writeStr(2, 1, "Hello, World !");
            sheet->writeNum(3, 1, 1000);
        }
        book->save("example.xls");
        book->release();
    }
    return 0;
}