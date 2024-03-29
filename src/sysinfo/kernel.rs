pub fn get_kernel_version() -> String {
    std::fs::read_to_string("/proc/sys/kernel/osrelease")
        .ok()
        .unwrap()
        .trim()
        .to_string()
}
