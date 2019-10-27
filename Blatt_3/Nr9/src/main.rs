use std::env;
use std::vec::Vec;

type Matrix = Vec<Vec<i64>>;

fn main() {
	let args: Vec<String> = env::args().collect();

	if args.len() != 4 {
		exit_with_error(&format!("ERROR: expecting 3 arguments. <Matrix1> <Operator> <Matrix2>. Got {} arguments.", args.len() - 1));
	}
	let matrix1 = pars_matrix(&args[1]);
	let matrix2 = pars_matrix(&args[3]);
	
	let result_matrix = match args[2].as_ref() {
		"+" => matrix_add(matrix1, matrix2),
		"*" => matrix_multiply(matrix1, matrix2),
		_ => exit_with_error(&format!("ERROR: unknown matrix operation {}", &args[2]))
	};
	matrix_print(result_matrix);
}

fn exit_with_error(error_msg: &String) -> ! {
	eprintln!("{}", error_msg);
	::std::process::exit(1);
}

fn pars_matrix(matrix_string: &String) -> Matrix {
	if matrix_string.is_empty() {
		return Vec::new();
	}
	let matrix: Matrix = matrix_string.split(";").map(|row: &str| { 
		row.split(",").map(|cell: &str| { 
			match cell.parse::<i64>() {
				Ok(num) => num,
				Err(_) => exit_with_error(&format!("ERROR: '{}' is not a number", cell))
			}
		}).collect()
	}).collect();
	
	if !matrix.is_empty() {
		let row_len = matrix[0].len();
		if !matrix.iter().all(|row| row.len() == row_len) {
			exit_with_error(&format!("ERROR: the matrix is malformed: {}", matrix_string));
		}
	};

	return matrix;
}

fn matrix_multiply(m1: Matrix, m2: Matrix) -> Matrix {
	if m1.is_empty() != m2.is_empty() {
		exit_with_error(&format!("Can't multiply empty matrix with non empty matrix"))
	}
	if m1.is_empty() && m2.is_empty() {
		return Vec::new();
	}
	if m1.len() != m2[0].len() {
		exit_with_error(&format!("Can't multiply matrix with {} rows with an matrix with {} columns", m1.len(), m2[0].len()));
	}
	if m1[0].len() != m2.len() {
		exit_with_error(&format!("Can't multiply matrix with {} columns with an matrix with {} rows", m1[0].len(), m2.len()));
	}
	
	let mut matrix_out: Matrix = Vec::new();
	//matrix_out.try_reserve(m1.len());
	for i in 0..m1.len() {
		let mut row_out: Vec<i64> = Vec::new();
		//row_out.try_reserve(m1.len());
		for j in 0..m1.len() {
			let mut sum = 0;
			for k in 0..m2.len() {
				sum += m1[i][k] * m2[k][j];
			}
			row_out.push(sum);
		}
		matrix_out.push(row_out);
	}
	return matrix_out;
}

fn matrix_add(m1: Matrix, m2: Matrix) -> Matrix {
	if m1.len() != m2.len() {
		exit_with_error(&format!("ERROR: Matrices don't have the same row count. Matrix 1 has {} rows. Matrix 2 has {} rows.", m1.len(), m2.len()));
	}
	if m1.is_empty() {
		return Vec::new();
	} else {
		if m1[0].len() != m2[0].len() {
			exit_with_error(&format!("ERROR: Matrices don't have the same column count. Matrix 1 has {} column. Matrix 2 has {} column.", m1[0].len(), m2[0].len()));
		}
	}
	return m1.iter().enumerate().map(|(i, row)| {
		row.iter().enumerate().map(|(j, value)| {
			value + m2[i][j]
		}).collect()
	}).collect();
}

fn matrix_print(m: Matrix) {
	let mut s = String::new();
	for (i, row) in m.iter().enumerate() {
		for (j, value) in row.iter().enumerate() {
			s.push_str(value.to_string().as_ref());
			if j < row.len() - 1 {
				s.push(',');
			}
		}
		if i < m.len() - 1 {
			s.push(';');
		}
	}
	println!("{}", s);
}