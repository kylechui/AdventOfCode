import gleam/bool
import gleam/int
import gleam/io
import gleam/list
import gleam/pair
import gleam/string

const xmas = "XMAS"

fn count(input: String, sub: String) -> Int {
  input |> string.split(on: sub) |> list.length |> int.subtract(1)
}

pub fn diagonalize(input: List(String)) -> List(String) {
  input
  |> list.index_map(fn(line, row) {
    line
    |> string.to_graphemes
    |> list.index_map(fn(char, col) { #(#(row, col), char) })
  })
  |> list.flatten
  // Chunk along diagonals: The row + col will be constant
  |> list.sort(fn(e1, e2) { int.compare(e1.0.0 + e1.0.1, e2.0.0 + e2.0.1) })
  |> list.chunk(fn(e) { e.0.0 + e.0.1 })
  |> list.map(list.map(_, pair.second))
  |> list.map(string.join(_, with: ""))
}

pub fn pt_1(input: String) -> Int {
  let grid = input |> string.split(on: "\n")
  let r_count = grid |> list.map(count(_, xmas)) |> int.sum
  let l_count =
    grid |> list.map(string.reverse) |> list.map(count(_, xmas)) |> int.sum

  let transpose_grid =
    grid
    |> list.map(string.to_graphemes)
    |> list.transpose
    |> list.map(string.join(_, with: ""))
  let d_count = transpose_grid |> list.map(count(_, xmas)) |> int.sum
  let u_count =
    transpose_grid
    |> list.map(string.reverse)
    |> list.map(count(_, xmas))
    |> int.sum

  let diag_grid = diagonalize(grid)
  let dr_count = diag_grid |> list.map(count(_, xmas)) |> int.sum
  let ul_count =
    diag_grid |> list.map(string.reverse) |> list.map(count(_, xmas)) |> int.sum

  let diag_reverse_grid = diagonalize(grid |> list.map(string.reverse))
  let ur_count = diag_reverse_grid |> list.map(count(_, xmas)) |> int.sum
  let dl_count =
    diag_reverse_grid
    |> list.map(string.reverse)
    |> list.map(count(_, xmas))
    |> int.sum

  u_count
  + d_count
  + l_count
  + r_count
  + ul_count
  + ur_count
  + dl_count
  + dr_count
}

fn window(str: String, size: Int) -> List(String) {
  str
  |> string.to_graphemes
  |> list.window(size)
  |> list.map(string.join(_, with: ""))
}

fn zip3(lst1: List(a), lst2: List(a), lst3: List(a)) -> List(#(a, a, a)) {
  case lst1, lst2, lst3 {
    [], _, _ -> []
    _, [], _ -> []
    _, _, [] -> []
    [h1, ..t1], [h2, ..t2], [h3, ..t3] -> [#(h1, h2, h3), ..zip3(t1, t2, t3)]
  }
}

fn x_mas(input: #(String, String, String)) -> Bool {
  let assert [_, center, _] = string.to_graphemes(input.1)
  use <- bool.guard(when: center != "A", return: False)
  {
    string.starts_with(input.0, "M")
    && string.ends_with(input.2, "S")
    || string.starts_with(input.0, "S")
    && string.ends_with(input.2, "M")
  }
  && {
    string.ends_with(input.0, "M")
    && string.starts_with(input.2, "S")
    || string.ends_with(input.0, "S")
    && string.starts_with(input.2, "M")
  }
}

pub fn pt_2(input: String) -> Int {
  input
  |> string.split(on: "\n")
  |> list.map(window(_, 3))
  |> list.window(3)
  |> list.map(fn(rows) {
    let assert [r1, r2, r3] = rows
    zip3(r1, r2, r3)
  })
  |> list.flatten
  |> list.map(x_mas)
  |> list.count(fn(b) { b == True })
}
