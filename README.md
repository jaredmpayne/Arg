# arg

## A stupid simple argument parser for C++.

`arg` is a command line argument parser with virtually no learning curve. It
relies only on the C++ Standard Template Library.

### Example

```c++
#include <string>
#include <vector>

#include "arg/Parser.hpp"

int main(int argc, const char **argv) {
    arg::Parser parser;

    // Add long options.
    parser.add_option({ "version" });

    // Add short options.
    parser.add_option({ "f" });
    parser.add_option({ "r" });

    // Long and short options are automatically differentiated between.
    parser.add_option({ "help", "h" });

    // Positional arguments are added to the last option raised, with a limit you define.
    // Options can be assigned to with either syntax: `--output=foo.txt` or `--output foo.txt`.
    parser.add_option({ "output", "o" }, 1);

    // So if the arguments were "foo --help -ru -o foo.txt bar --blah"...
    parser.parse(std::vector<std::string>(argv, argv + argc));

    // ...then all of the following expressions would be true.
    parser.executable_argument() == "foo";

    parser.has_raised_option("h");
    parser.has_raised_option("r");
    parser.has_raised_option("help");

    !parser.has_raised_option("f");

    parser.has_raised_option("output");
    parser.option_values("output") == std::vector<std::string>({ "foo.txt" });

    parser.unrecognized_arguments() == std::vector<std::string>({ "-u", "bar", "--blah" });
}

```

This example covers the entire interface. Check the inline header documentation
if you still want more information on individual functions.

### Building

`arg` is intended to be imported and built using the
[spur package manager](https://github.com/jaredmpayne/spur"). To import `arg`
into your project, just add it to your package dependencies in `spur.json` and
as a target dependency to any target that will `#include "arg/Parser.hpp"`.

```json
{
    "name": "your_package",
    "dependencies": [
        {
            "url": "https://github.com/jaredmpayne/arg.git",
            "version": "1.0"
        }
    ],
    "products": [
        {
            "name": "your_package",
            "type": "library",
            "targets": ["your_package"]
        }
    ],
    "targets": [
        {
            "name": "your_package",
            "dependencies": ["arg"]
        }
    ],
    "tests": [
        {
            "name": "your_package_tests",
            "dependencies": ["your_package"]
        }
    ]
}
```
