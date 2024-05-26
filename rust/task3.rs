use std::f64::consts::E;
use std::io;
use std::iter::Iterator;

fn korrel(temperatures: &Vec<f64>, mean_y: f64, t: usize) -> f64 {
    let mut sum_xy = 0.0;
    let mut sum_x2 = 0.0;
    let mut sum_y2 = 0.0;
    let mean_x = (t as f64) / 2.0;
    for i in 0..=t {
        sum_xy += (i as f64 - mean_x) * (temperatures[i] - mean_y);
        sum_x2 += (i as f64 - mean_x) * (i as f64 - mean_x);
        sum_y2 += (temperatures[i] - mean_y) * (temperatures[i] - mean_y);
    }
    sum_xy / (sum_x2 * sum_y2).sqrt()
}

fn aprox(x_vector: &Vec<f64>, y_vector: &Vec<f64>) -> (f64, f64) {
    let n = x_vector.len();
    let mut sum_x = 0.0;
    let mut sum_y = 0.0;
    let mut sum_xy = 0.0;
    let mut sum_x2 = 0.0;
    for i in 0..n {
        sum_x += x_vector[i];
        sum_y += y_vector[i];
        sum_xy += x_vector[i] * y_vector[i];
        sum_x2 += x_vector[i] * x_vector[i];
    }
    let a = (n as f64 * sum_xy - sum_x * sum_y) / (n as f64 * sum_x2 - sum_x * sum_x);
    let b = (sum_y - a * sum_x) / (n as f64);
    (a, b)
}

fn coffee(T: f64, Ts: f64, r: f64, time_limit: usize) -> Vec<(f64, f64)> {
    let mut temperatures = Vec::new();
    let mut times = Vec::new();
    let mut temp_corr = Vec::new();
    for t in 0..=time_limit {
        let temperature = Ts + (T - Ts) * E.powf(-r * t as f64);
        temperatures.push(temperature);
        times.push(t as f64);
    }
    let (a, b) = aprox(&times, &temperatures);
    let mean_y = temperatures.iter().sum::<f64>() / temperatures.len() as f64;
    for t in 0..=time_limit {
        let corr = korrel(&temperatures, mean_y, t);
        temp_corr.push((temperatures[t], corr));
    }
    temp_corr
}

fn main() {
    let mut T: f64 = 0.0;
    let mut Ts: f64 = 0.0;
    let mut r: f64 = 0.0;
    let mut time_limit: usize = 0;

    println!("Введите начальную температуру кофе: ");
    T = read_input();
    println!("Введите температуру окружающей среды: ");
    Ts = read_input();
    println!("Введите коэффициент остывания: ");
    r = read_input();
    println!("Введите итоговое время: ");
    time_limit = read_input_usize();

    let results = coffee(T, Ts, r, time_limit);

    let (a, b) = aprox(&(0..=time_limit as isize).map(|x| x as f64).collect(), &results.iter().map(|x| x.0).collect());
    println!("Коэффициенты аппроксимирующей прямой a - {}, b - {}", a, b);
    println!("+------+------------+---------------+");
    println!("| Время| Температура| Коэф.кореляции|");
    println!("+------+------------+---------------+");
    for (t, result) in results.iter().enumerate() {
        println!("|{:6}|{:12.4}|{:15.4}|", t, result.0, result.1);
        println!("+------+------------+---------------+");
    }
}

fn read_input() -> f64 {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read input");
    input.trim().parse().expect("Invalid input")
}

fn read_input_usize() -> usize {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read input");
    input.trim().parse().expect("Invalid input")
}
