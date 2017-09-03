# Contributing to Photon
Hey, thanks for your interest in contributing to Photon! If you want to get up
to speed on the innner workings of the library, [Implementation.md] is a good
place to start. Beyond that, the source code is your next best bet to understand
how this library works. Also, remember that Photon is licensed under the
[MIT License].

Once you've written a contribution, submit it with a PR with a description of
what changes were made

## Branch structure
* `master` is the branch for ready-to-use code. It should compile and have no
  known bugs
* `develop` is the branch for code that compiles but isn't ready to be pushed to
  `master`. Features on `develop` should compile and not always crash, but may
  have bugs or undefined/unimplemented/unintended behavior
* New features exist in their own branches, whose names should be patterend as
  `feature-<feature-name>`
* If a patch is necessary, it can be developed in a `patch-<patch-name>` branch
* Other things, such as documentation updates or miscellaneous changes can go in
  a `misc-<change>` branch


## Code style
At the end of the day, `camelCase` vs `underscore_names` isn't that important,
but consistency is. 

* Photon is based on classes and polymorphic concepts, but if a standalone
  function makes sense, do it
* Prefer descriptive names over brevity
* Public and protected variables and functions are in `camelCase`
* Class and Struct names are in `CamelCase`
* Private variables are prefixed with `_`, such as `_myVar`
* Opening braces are on the same line
* Template code definitions go in `.ipp` files instead of the headers


[Implementation.md]: ./Implementation.md
[MIT License]: ../LICENSE.md
