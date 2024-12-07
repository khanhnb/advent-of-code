use std::{
    cmp::Ordering,
    collections::{HashMap, HashSet},
    fs::File,
    io::{BufReader, Lines},
    time::Instant,
};

pub fn run(lines: Lines<BufReader<File>>) {
    let mut first_section = true;
    let mut m: HashMap<u32, HashSet<u32>> = HashMap::new();
    let mut u = vec![];

    for line in lines.flatten() {
        if line == "" {
            first_section = false;
            continue;
        }
        if first_section {
            // read page ordering rules
            let ordering_rule = line
                .split('|')
                .map(|x| x.parse::<u32>().unwrap())
                .collect::<Vec<_>>();
            if let Some(page) = m.get_mut(&ordering_rule[0]) {
                page.insert(ordering_rule[1]);
            } else {
                m.insert(ordering_rule[0], HashSet::from([ordering_rule[1]]));
            }
        } else {
            //read update section
            let update = line
                .split(',')
                .map(|x| x.parse::<u32>().unwrap())
                .collect::<Vec<_>>();
            u.push(update);
        }
    }

    let now = Instant::now();
    println!("Part 1: {}", part1(&m, &u));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);

    let now = Instant::now();
    println!("Part 2: {}", part2(&m, &u));
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);
}

fn part1(m: &HashMap<u32, HashSet<u32>>, u: &Vec<Vec<u32>>) -> u32 {
    let mut ans = 0;
    for update in u {
        let mut valid = true;
        for i in 1..update.len() {
            let list = m.get(&update[i]);
            if let Some(list) = list {
                if list.contains(&update[i - 1]) {
                    valid = false;
                    break;
                }
            }
        }
        if valid {
            ans += update[update.len() / 2];
        }
    }
    ans
}

fn part2(m: &HashMap<u32, HashSet<u32>>, u: &Vec<Vec<u32>>) -> u32 {
    let mut ans = 0;
    for update in u {
        let mut valid = true;
        for i in 1..update.len() {
            let list = m.get(&update[i]);
            if let Some(list) = list {
                if list.contains(&update[i - 1]) {
                    valid = false;
                    break;
                }
            }
        }
        if !valid {
            // reorder the update
            let mut ordered_update = update.clone();
            // Improve: Can we sort the whole list of pages instead of sorting each list?
            ordered_update.sort_by(|a, b| {
                if let Some(c) = m.get(a) {
                    if c.contains(b) {
                        return Ordering::Less;
                    }
                }
                if let Some(c) = m.get(b) {
                    if c.contains(a) {
                        return Ordering::Greater;
                    }
                }
                return Ordering::Equal;
            });
            ans += ordered_update[ordered_update.len() / 2];
        }
    }
    ans
}
