use std::{
    collections::HashMap,
    fs::File,
    io::{BufReader, Lines}, time::Instant,
};

pub fn run(lines: Lines<BufReader<File>>) {
    let mut f_locations = vec![];
    let mut s_locations = vec![];
    for line in lines {
        let line = line.unwrap();
        let mut iter = line.split_whitespace();
        let f_location = iter.next().unwrap().parse::<u32>().unwrap();
        let s_location = iter.next().unwrap().parse::<u32>().unwrap();
        f_locations.push(f_location);
        s_locations.push(s_location);
    }
    let now = Instant::now();
    println!("part 1: {}", part1(&mut f_locations, &mut s_locations));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);
    let now = Instant::now();
    println!("part 2: {}", part2(&mut f_locations, &mut s_locations));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);
}

fn part1(f: &mut Vec<u32>, s: &mut Vec<u32>) -> u32 {
    // TODO: implement counting sort
    f.sort();
    s.sort();
    let mut res = 0;
    for i in 0..f.len() {
        res += f[i].abs_diff(s[i]);
    }
    res
}

fn part2(f: &mut Vec<u32>, s: &mut Vec<u32>) -> u32 {
    let mut res = 0;
    let mut counter = HashMap::<u32, u32>::new();

    for i in 0..s.len() {
        if let Some(val) = counter.get_mut(&s[i]) {
            *val += 1;
        } else {
            counter.insert(s[i], 1);
        }
    }

    for i in 0..f.len() {
        res += f[i] * counter.get(&f[i]).unwrap_or(&0);
    }
    res
}
