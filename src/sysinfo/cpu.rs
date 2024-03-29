use std::fs::File;
use std::io::Read;

pub fn get_cpu() -> String {
    let mut file = File::open("/proc/cpuinfo").unwrap();
    let mut temp = String::new();
    file.read_to_string(&mut temp).unwrap();

    for line in temp.lines() {
        if let Some(cpu) = line.strip_prefix("model name") {
            let cpu = cpu.replace(": ", "");
            return cpu.trim().to_string();
        }
    }
    "Cpu not found".to_string()
}
