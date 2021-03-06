/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
@brief Utility for compiling data resources via command-line.

Produces compiled C++ file with data in hexadecimal representation. Status
messages are printed to standard output, errors are printed to error output.
See `corrade-rc --help` for command-line parameters, see @ref resource-management
for brief introduction.
*/

#include "Corrade/Containers/Array.h"
#include "Corrade/Utility/Arguments.h"
#include "Corrade/Utility/Debug.h"
#include "Corrade/Utility/Directory.h"
#include "Corrade/Utility/Resource.h"

#ifndef DOXYGEN_GENERATING_OUTPUT
int main(int argc, char** argv) {
    Corrade::Utility::Arguments args;
    args.addArgument("name")
        .addArgument("conf").setHelpKey("conf", "resources.conf")
        .addArgument("out").setHelpKey("out", "outfile.cpp")
        .setCommand("corrade-rc")
        .setHelp("Resource compiler for Corrade.")
        .parse(argc, argv);

    /* Remove previous output file */
    Corrade::Utility::Directory::rm(args.value("out"));

    /* Compile file */
    const std::string compiled = Corrade::Utility::Resource::compileFrom(args.value("name"), args.value("conf"));

    /* Compilation failed */
    if(compiled.empty()) return 2;

    /* Save output */
    if(!Corrade::Utility::Directory::write(args.value("out"), {compiled.data(), compiled.size()})) {
        Corrade::Utility::Error() << "Cannot write output file " << '\'' + args.value("out") + '\'';
        return 3;
    }

    return 0;
}
#endif
