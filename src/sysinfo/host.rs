use std::fs::File;
use std::io::Read;

pub fn get_hostname() -> String {
    let mut file = File::open("/proc/sys/kernel/hostname").unwrap();
    let mut hostname = String::new();
    file.read_to_string(&mut hostname).unwrap();
    let hostname = hostname.replace("\n", "");
    hostname
}
