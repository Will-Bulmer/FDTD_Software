### CMakeLists

You would need to update your `CMakeLists.txt` if:

1. **You're including external libraries**. For example, if you're including headers from an external library like `boost`, `SFML`, `nlohmann-json`, or any other non-standard library, you'd typically need to find the package and link against it.

2. **You're including headers from your own project** that reside in directories not already added by `include_directories()` or `target_include_directories()`.