# Mackeys

Often OS-defined key mappings may be overridden by user applications. This
driver maps useful key combinations from MacOS into the Kernel.

**NOTE:** Loading this module into the Kernel will prevent certain
key bindings in applications from properly functioning. Any functionality,
would then have to be remapped to new keys at the application level.

# Compiling & Running

Run `make`

Run `sudo insmod ./mackeys.ko` to load the module into the Kernel.

Run `sudo rmmod mackeys` to unload the module from the Kernel.

# [License](./LICENSE.md)
