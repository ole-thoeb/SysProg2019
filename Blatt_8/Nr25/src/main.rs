use std::env;
use std::vec::Vec;
use std::thread;
use std::sync::Arc;

#[derive(Debug)]
//define Matrix struct (2-D Vector)
struct Matrix {
	values: Vec<Vec<i64>>,
	m: usize, //num of rows
	n: usize //num of columns
}

//member funcs
impl Matrix {

	//multiplication
	fn dot(&self, other: &Matrix) -> Matrix {
		if self.values.is_empty() != other.values.is_empty() {
			exit_with_error(&format!("Can't multiply empty matrix with non empty matrix"))
		}
		if self.values.is_empty() && other.values.is_empty() {
			return Matrix::new(0, 0);
		}
		if self.m != other.n {
			exit_with_error(&format!("Can't multiply matrix with {} rows with an matrix with {} columns", self.m, other.n));
		}
		if self.n != other.m {
			exit_with_error(&format!("Can't multiply matrix with {} columns with an matrix with {} rows", self.n, other.m));
		}
		let m = self.m;
		let n = other.n;
		let mut matrix_out: Matrix = Matrix::new(m, n);
		//matrix_out.try_reserve(m1.len());
		for i in 0..m {
			//row_out.try_reserve(m1.len());
			for j in 0..n {
				let mut sum = 0;
				for k in 0..other.m {
					sum += self.values[i][k] * other.values[k][j];
				}
				matrix_out.values[i][j] = sum;
			}
		}
		return matrix_out;
	}

    //addition
	fn add(&self, other: &Matrix) -> Matrix {
		if self.m != other.m {
			exit_with_error(&format!("ERROR: Matrices don't have the same row count. Matrix 1 has {} rows. Matrix 2 has {} rows.", self.m, other.m));
		}
		if self.m == 0 {
			return Matrix::new(0, 0);
		} else if self.n != other.n {
			exit_with_error(&format!("ERROR: Matrices don't have the same column count. Matrix 1 has {} column. Matrix 2 has {} column.", self.n, other.n));
		}
		let values: Vec<Vec<i64>> = self.values.iter().enumerate().map(|(i, row)| {
			row.iter().enumerate().map(|(j, value)| {
				value + other.values[i][j]
			}).collect()
		}).collect();
		return Matrix{ values: values, m: self.m, n: self.n };
    }

    //"constructor"
	pub fn new(m: usize, n: usize) -> Matrix {
		let mut result_vec: Vec<Vec<i64>> = Vec::new();

		//create matrix
		for _ in 0..m {
			result_vec.push(vec![0; n]);
		}

		Matrix{values: result_vec, m: m, n: n}
	}
}

//./target/debug/thread_matrix `./generate.out 100 100` + `./generate.out 100 100` 8
fn main() {
	let args: Vec<String> = env::args().collect();

	if args.len() < 4 {
		exit_with_error(&format!("ERROR: expecting 3 arguments. <Matrix1> <Operator> <Matrix2> <Thread-number>(Optional). Got {} arguments.", args.len() -1));
	}
	let matrix1 = Arc::new(pars_matrix(&args[1]));
	let matrix2 = Arc::new(pars_matrix(&args[3]));
	let thread_num = if args.len() >= 5 {
		args[4].parse::<usize>().unwrap()
	} else {
		1usize
	};
	
	let result_matrix = if thread_num == 1 {
		match args[2].as_ref() {
			"+" => matrix1.as_ref().add(matrix2.as_ref()),
			"*" => matrix1.as_ref().dot(matrix2.as_ref()),
			_ => exit_with_error(&format!("ERROR: unknown matrix operation {}", &args[2]))
		}
	} else {
		thread_op(matrix1, matrix2, args[2].as_ref(), thread_num)
	};
	matrix_print(result_matrix);

}

fn thread_op(m1: Arc<Matrix>, m2: Arc<Matrix>, operation: &str, thread_num: usize) -> Matrix {
	let mut threads = Vec::with_capacity(thread_num);
	for i in 0..thread_num {
		let local_m1 = m1.clone();
		let local_m2 = m2.clone();

		threads.push(
			match operation {
				"+" => thread::spawn(move || {
					skipped_add(local_m1.as_ref(), local_m2.as_ref(), i, thread_num)
				}),
				"*" => thread::spawn(move || {
					skipped_mul(local_m1.as_ref(), local_m2.as_ref(), i, thread_num)
				}),
				_ => exit_with_error(&format!("ERROR: unknown matrix operation {}", operation))
			}
		);
	}
	let mut res_matrix = Matrix::new(m1.m, m2.n);
	for thread in threads {
		let m = thread.join().unwrap();
		for (i, row) in m.values.iter().enumerate() {
			for (j, value) in row.iter().enumerate() {
				if *value != 0 {
					res_matrix.values[i][j] = *value;
				}
			}
		}
	}
	res_matrix
}

//fn thread_add(m1: Arc<Matrix>, m2: Arc<Matrix>, thread_num: usize) -> Matrix {
//	let mut threads = Vec::with_capacity(thread_num);
//	for i in 0..thread_num {
//		let local_m1 = m1.clone();
//		let local_m2 = m2.clone();
//
//		threads.push(thread::spawn(move || {
//			skipped_add(local_m1.as_ref(), local_m2.as_ref(), i, thread_num)
//		}));
//	}
//	let mut res_matrix = Matrix::new(m1.m, m1.n);
//	for thread in threads {
//		let m = thread.join().unwrap();
//		for (i, row) in m.values.iter().enumerate() {
//			for (j, value) in row.iter().enumerate() {
//				if *value != 0 {
//					res_matrix.values[i][j] = *value;
//				}
//			}
//		}
//	}
//	res_matrix
//}

fn skipped_add(m1: &Matrix, m2: &Matrix, offset: usize, n: usize) -> Matrix {
	let mut res_matrix = Matrix::new(m1.m, m1.n);
	let mut i = offset;
	while i < m1.m * m1.n {
		let j = i % m1.m;
		let k = i / m1.n;
		res_matrix.values[j][k] = m1.values[j][k] + m2.values[j][k];
		i += n;
	}
	res_matrix
}

fn thread_mul(m1: Arc<Matrix>, m2: Arc<Matrix>, thread_num: usize) -> Matrix {
	let mut threads = Vec::with_capacity(thread_num);
	for i in 0..thread_num {
		let local_m1 = m1.clone();
		let local_m2 = m2.clone();

		threads.push(thread::spawn(move || {
			skipped_mul(local_m1.as_ref(), local_m2.as_ref(), i, thread_num)
		}));
	}
	let mut res_matrix = Matrix::new(m1.m, m2.n);
	for thread in threads {
		let m = thread.join().unwrap();
		for (i, row) in m.values.iter().enumerate() {
			for (j, value) in row.iter().enumerate() {
				if *value != 0 {
					res_matrix.values[i][j] = *value;
				}
			}
		}
	}
	res_matrix
}

fn skipped_mul(m1: &Matrix, m2: &Matrix, offset: usize, n: usize) -> Matrix {
	let mut res_matrix = Matrix::new(m1.m, m2.n);
	let mut o = offset;
	while o < m1.m * m1.n {
		let i = o % m1.m;
		let j = o / m1.n;

		let mut sum = 0;
		for k in 0..m2.m {
			sum += m1.values[i][k] * m2.values[k][j];
		}
		res_matrix.values[i][j] = sum;
		o += n;
	}
	res_matrix
}

fn exit_with_error(error_msg: &String) -> ! {
	eprintln!("{}", error_msg);
	::std::process::exit(1);
}

fn pars_matrix(matrix_string: &String) -> Matrix {
	if matrix_string.is_empty() {
		return Matrix::new(0, 0);
	}
	let values: Vec<Vec<i64>> = matrix_string.split(";").map(|row: &str| { 
		row.split(",").map(|cell: &str| { 
			match cell.parse::<i64>() {
				Ok(num) => num,
				Err(_) => exit_with_error(&format!("ERROR: '{}' is not a number", cell))
			}
		}).collect()
	}).collect();
	
	return if !values.is_empty() {
		let row_len = values[0].len();
		if !values.iter().all(|row| row.len() == row_len) {
			exit_with_error(&format!("ERROR: the matrix is malformed: {}", matrix_string));
		}
		let m = values.len();
		Matrix{values: values, m: m, n: row_len}
	} else {
		Matrix::new(0, 0)
	};
}

fn matrix_print(m: Matrix) {
	let mut s = String::new();
	for (i, row) in m.values.iter().enumerate() {
		for (j, value) in row.iter().enumerate() {
			s.push_str(value.to_string().as_ref());
			if j < row.len() - 1 {
				s.push(',');
			}
		}
		if i < m.values.len() - 1 {
			s.push(';');
		}
	}
	println!("{}", s);
}