use std::fs::File;
use std::io::Read;

pub fn get_distro() -> String {
    let mut file = File::open("/etc/os-release").unwrap();
    let mut temp = String::new();
    file.read_to_string(&mut temp).unwrap();

    for line in temp.lines() {
        if line.starts_with("NAME=") {
            let line = line.strip_prefix("NAME=").unwrap();
            return line.to_string();
        }
    }
    "Distro not found".to_string()
}

pub fn get_distro_id() -> String {
    let mut file = File::open("/etc/os-release").unwrap();
    let mut temp = String::new();
    file.read_to_string(&mut temp).unwrap();

    for line in temp.lines() {
        if line.starts_with("ID=") {
            let line = line.strip_prefix("ID=").unwrap();
            return line.to_string();
        }
    }
    "Distro id not found".to_string()
}
