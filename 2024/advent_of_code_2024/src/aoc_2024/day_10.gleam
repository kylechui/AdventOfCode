import gleam/bool
import gleam/dict.{type Dict}
import gleam/function
import gleam/int
import gleam/io
import gleam/list
import gleam/order.{Eq, Gt, Lt}
import gleam/pair
import gleam/result
import gleam/set.{type Set}
import gleam/string

fn parse_int(str: String) -> Int {
  str |> int.parse |> result.unwrap(-1)
}

fn make_grid(str: String) -> Dict(#(Int, Int), Int) {
  str
  |> string.split(on: "\n")
  |> list.index_map(fn(line, i) {
    list.index_map(string.to_graphemes(line), fn(c, j) {
      #(#(i, j), parse_int(c))
    })
  })
  |> list.flatten
  |> dict.from_list
}

fn dfs(
  grid: Dict(#(Int, Int), Int),
  seen: Set(#(Int, Int)),
  i: Int,
  j: Int,
  val: Int,
) -> Set(#(Int, Int)) {
  case dict.get(grid, #(i, j)) {
    Error(Nil) -> set.new()
    Ok(9) if val == 9 -> set.from_list([#(i, j)])
    Ok(found) if val == found ->
      dfs(grid, seen, i + 1, j, val + 1)
      |> set.union(dfs(grid, seen, i - 1, j, val + 1))
      |> set.union(dfs(grid, seen, i, j + 1, val + 1))
      |> set.union(dfs(grid, seen, i, j - 1, val + 1))
    Ok(_) -> set.new()
  }
}

fn dfs2(grid: Dict(#(Int, Int), Int), i: Int, j: Int, val: Int) -> Int {
  case dict.get(grid, #(i, j)) {
    Error(Nil) -> 0
    Ok(9) if val == 9 -> 1
    Ok(found) if val == found ->
      dfs2(grid, i + 1, j, val + 1)
      + dfs2(grid, i - 1, j, val + 1)
      + dfs2(grid, i, j + 1, val + 1)
      + dfs2(grid, i, j - 1, val + 1)
    Ok(_) -> 0
  }
}

pub fn pt_1(input: String) -> Int {
  let grid = make_grid(input)
  grid
  |> dict.keys
  |> list.map(fn(pos) { dfs(grid, set.new(), pos.0, pos.1, 0) })
  |> list.map(set.size)
  |> int.sum
}

pub fn pt_2(input: String) -> Int {
  let grid = make_grid(input)
  grid
  |> dict.keys
  |> list.map(fn(pos) { dfs2(grid, pos.0, pos.1, 0) })
  |> int.sum
}
