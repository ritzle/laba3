use rand::Rng;
use std::collections::HashSet;
use std::time::SystemTime;

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

fn builder_test(prime: &Vec<usize>, bit: usize) -> (usize, Vec<usize>) {
    let mut rng = rand::thread_rng();
    let max_index = prime.iter().position(|&p| p >= 2_usize.pow((bit - 1) as u32)).unwrap();
    let max_pow = (2_usize.pow((bit - 1) as u32)).leading_zeros() as usize;
    let mut m = 1;
    let mut q = Vec::new();

    loop {
        let num = rng.gen_range(0..max_index);
        let power = rng.gen_range(1..=max_pow);
        let p = prime[num].pow(power as u32);

        if m * p < usize::MAX {
            m *= p;
            q.push(prime[num]);
        }

        if m > 2_usize.pow((bit - 2) as u32) {
            if m >= 2_usize.pow((bit - 1) as u32) {
                m = 1;
                q.clear();
            } else {
                break;
            }
        }
    }

    (2 * m + 1, q)
}

fn test_millera(n: usize, t: usize, q: &[usize]) -> usize {
    let mut a = Vec::new();

    while a.len() != t {
        let aj = rng(2, n - 1);
        if !a.contains(&aj) {
            a.push(aj);
        }
    }

    for aj in &a {
        if power_mod(*aj, n - 1, n) != 1 {
            return 0;
        }
    }

    let mut flag = true;
    let mut i = 0;
    for aj in &a {
        if q.get(i).unwrap_or(&0) != &0 && power_mod(*aj, (n - 1) / q[i], n) != 1 {
            flag = false;
            if i < q.len() {
                i += 1;
            }
        }
    }

    if flag {
        0
    } else {
        1
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

fn rng(a: usize, b: usize) -> usize {
    let mut rng = rand::thread_rng();
    rng.gen_range(a..=b)
}

fn main() {
    let prime = primes(500);
    let bit = read_input();
    let mut res: HashSet<usize> = HashSet::new();
    let mut res_ver_test = Vec::new();
    let mut otvegnutie = Vec::new();
    let mut k = 0;

    while res.len() < 10 {
        let (n, q) = builder_test(&prime, bit);
        let probability = test_millera(n, 10, &q);

        if probability == 1 {
            if !res.contains(&n) {
                res.insert(n);
                let probability_verify = test_millera(n, 1, &q);
                if probability_verify == 1 {
                    res_ver_test.push("+".to_string());
                } else {
                    res_ver_test.push("-".to_string());
                }
                otvegnutie.push(k);
                k = 0;
            }
        } else {
            k += 1;
        }
    }

    print_results(&res.into_iter().collect::<Vec<_>>(), &res_ver_test, &otvegnutie);
}

fn read_input() -> usize {
    let mut input = String::new();
    std::io::stdin()
        .read_line(&mut input)
        .expect("Failed to read input");
    input.trim().parse().expect("Invalid input")
}

fn print_results(res: &[usize], res_ver_test: &[String], otvegnutie: &[usize]) {
    println!("Prime Numbers\tTest Results\tOccurrences");
    println!("----------------------------------------------");

    for i in 0..res.len() {
        println!("{}\t\t{}\t\t{}", res[i], res_ver_test[i], otvegnutie[i]);
    }
}
