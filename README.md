# Conan Starter Project

Starter Conan project that can be used for more general projects.

If you do not already have setup Conan. Before you build this project.

Be sure to follow the [getting started](https://engine3d-dev.github.io/0.1/getting_started/) page.

## Building the Starter

!!! tip
> `-b missing` is to make sure dependencies for your project are available before linking into your project from the conan cache.

conan build . -b missing