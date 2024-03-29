use std::io::Read;

pub fn get_cpu() -> String {
    let mut file = std::fs::File::open("/proc/cpuinfo").unwrap();
    let mut cpuinfo = String::new();
    file.read_to_string(&mut cpuinfo).unwrap();
    for line in cpuinfo.lines() {
        if line.starts_with("model name:") {
            println!("{}", line);
        }
        //return;
    }
    cpuinfo
}
