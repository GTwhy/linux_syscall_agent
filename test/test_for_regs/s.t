execve("./ccc", ["./ccc"], 0xffffeefc82e0 /* 24 vars */) = 0
brk(NULL)                               = 0x2d255000
brk(0x2d255f80)                         = 0x2d255f80
uname({sysname="Linux", nodename="lsca", ...}) = 0
readlinkat(AT_FDCWD, "/proc/self/exe", "/root/pro/test/test_for_regs/ccc", 4096) = 32
brk(0x2d276f80)                         = 0x2d276f80
brk(0x2d277000)                         = 0x2d277000
fstat(1, {st_mode=S_IFCHR|0600, st_rdev=makedev(136, 0), ...}) = 0
write(1, "1,2,3,4,5,6,7,8,9,a", 19)     = 19
exit_group(0)                           = ?
+++ exited with 0 +++
