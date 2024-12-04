use std::{
    fs::File,
    io::{BufReader, Lines},
    time::Instant,
};

pub fn run(lines: Lines<BufReader<File>>) {
    let mut reports = vec![];
    for line in lines {
        let line = line.unwrap();
        let mut values: Vec<i32> = Vec::new();
        for val in line.split(' ') {
            values.push(val.parse::<i32>().unwrap());
        }
        reports.push(values);
    }
    let now = Instant::now();
    println!("Part 1: {}", part1(&reports));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);

    let now = Instant::now();
    println!("Part 2: {}", part2(&reports));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);
}

fn part1(reports: &Vec<Vec<i32>>) -> u32 {
    let mut res = 0;
    for report in reports {
        if is_safe(report) {
            res += 1;
        }
    }
    res
}

fn is_safe(report: &Vec<i32>) -> bool {
    let mut r = report.clone();
    let mut sum = 0;
    let mut abs_sum = 0;
    for i in 1..r.len() {
        r[i] -= report[i - 1];
        if r[i].abs() > 3 || r[i] == 0 {
            return false;
        }
        sum += r[i];
        abs_sum += r[i].abs();
    }
    if sum.abs() != abs_sum {
        return false;
    }
    true
}

fn is_safe_v2(report: &Vec<i32>) -> bool {
    let mut reports = Vec::new();
    reports.push(report.clone());
    for i in 0..report.len() {
        let mut tmp = report.clone();
        tmp.remove(i);
        reports.push(tmp);
    }
    for i in 0..reports.len() {
        if is_safe(&reports[i]) {
            return true;
        }
    }
    false
}

fn part2(reports: &Vec<Vec<i32>>) -> u32 {
    let mut res = 0;
    for report in reports {
        if is_safe_v2(report) {
            res += 1;
        }
    }
    res
}
