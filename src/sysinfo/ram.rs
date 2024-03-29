use std::fs::File;
use std::io::Read;

pub fn get_memory_usage() -> String {
    let mut file = File::open("/proc/meminfo").unwrap();
    let mut contents = String::new();
    file.read_to_string(&mut contents).unwrap();

    let mut memtotal: f32 = 0.0;
    let mut memused: f32 = 0.0;

    for line in contents.lines() {
        let mut line = line.replace("  ", "").replace(" kB", "");

        if line.starts_with("MemTotal:") {
            let line = line.replace("MemTotal: ", "");
            let temp = line.parse::<f32>().unwrap();
            memtotal = format!("{:.2}", temp / 1024 as f32 / 1024 as f32)
                .parse::<f32>()
                .unwrap();
        } else if line.starts_with("MemAvailable: ") {
            line = line.replace("MemAvailable: ", "");
            let temp = line.parse::<f32>().unwrap();
            memused = format!("{:.2}", temp / 1024 as f32 / 1024 as f32)
                .parse::<f32>()
                .unwrap();
            memused = memtotal - memused;
        }
    }

    if memtotal == 0.0 || memused == 0.0 {
        return "Not found".to_string();
    }
    format!("{} GiB / {} GiB", memused, memtotal)
}
