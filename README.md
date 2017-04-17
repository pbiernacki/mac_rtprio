# mac_rtprio
Simple MAC Framework policy to manage access for setting realtime priorities by selected GID.

To test, clone the repo and run `make && make load` in the module directory.  The load action require root permissions.

Set GID that should be able to change realtime priorities: `sysctl security.mac.rtprio.gid=1001` and enable enforcing:
`sysctl security.mac.rtprio.enabled=1`.

