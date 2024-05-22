extern crate rand;

use rand::Rng;
use std::collections::HashSet;

fn primes(n: usize) -> Vec<usize> {
    let mut is_prime = vec![true; n + 1];
    is_prime[0] = false;
    is_prime[1] = false;
    let mut primes = Vec::new();

    for p in 2..=(n as f64).sqrt() as usize {
        if is_prime[p] {
            for i in (p * p..=n).step_by(p) {
                is_prime[i] = false;
            }
        }
    }

    for p in 2..=n {
        if is_prime[p] {
            primes.push(p);
        }
    }

    primes
}

fn build_new_from_old(prime: &Vec<usize>, bit: usize) -> usize {
    let mut rng = rand::thread_rng();
    let max_index = prime.iter().position(|&p| p >= 2_usize.pow(bit as u32 / 2)).unwrap();
    let mut q;

    loop {
        q = prime[rng.gen_range(0..max_index)];
        if q > 2_usize.pow((bit as u32 / 2) - 1) && q <= 2_usize.pow(bit as u32 / 2) - 1 {
            break;
        }
    }

    loop {
        let n = (2_usize.pow(bit as u32 - 1) / q) as f64
            + (2_usize.pow(bit as u32 - 1) as f64 * rng.gen_range(0.0..1.0) / q);
        let mut p = (n as usize + 1) * q + 1;

        while p <= 2_usize.pow(bit as u32) {
            if power_mod(2, p - 1, p) == 1 && power_mod(2, n as usize + 1, p) != 1 {
                return p;
            }
            p += 2;
        }
    }
}

fn power_mod(a: usize, b: usize, n: usize) -> usize {
    let mut result = 1;
    let mut a = a;
    let mut b = b;

    while b > 0 {
        if b % 2 == 1 {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        b /= 2;
    }

    result
}

fn main() {
    let prime = primes(500);
    let bit = read_input();
    let mut res: HashSet<usize> = HashSet::new();

    while res.len() < 10 {
        let p = build_new_from_old(&prime, bit);
        res.insert(p);
    }

    print_res(&res.iter().collect::<Vec<_>>());
}

fn read_input() -> usize {
    let mut input = String::new();
    std::io::stdin()
        .read_line(&mut input)
        .expect("Failed to read input");
    input.trim().parse().expect("Invalid input")
}

fn print_res(res: &[&usize]) {
    for (i, p) in res.iter().enumerate() {
        println!("{}\t\t|\t\t{}", i + 1, p);
    }
}
