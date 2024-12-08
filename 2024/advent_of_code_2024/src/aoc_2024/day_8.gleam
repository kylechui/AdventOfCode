import gleam/bool
import gleam/dict.{type Dict}
import gleam/function
import gleam/int
import gleam/io
import gleam/list
import gleam/order.{Eq, Gt, Lt}
import gleam/pair
import gleam/set.{type Set}
import gleam/string

fn make_grid(input: String) -> Dict(#(Int, Int), String) {
  input
  |> string.split(on: "\n")
  |> list.index_map(fn(line, row_idx) {
    line
    |> string.to_graphemes
    |> list.index_map(fn(char, col_idx) { #(#(row_idx, col_idx), char) })
  })
  |> list.flatten
  |> dict.from_list
}

fn get_antinodes(antennas: List(#(#(Int, Int), String))) -> Set(#(Int, Int)) {
  antennas
  |> list.combination_pairs
  |> list.fold(set.new(), fn(set, p) {
    let #(#(pos1, _), #(pos2, _)) = p
    set
    |> set.insert(#(pos2.0 * 2 - pos1.0, pos2.1 * 2 - pos1.1))
    |> set.insert(#(pos1.0 * 2 - pos2.0, pos1.1 * 2 - pos2.1))
  })
}

fn get_all_antinodes(
  antennas: List(#(#(Int, Int), String)),
  in grid: Dict(#(Int, Int), String),
) -> Set(#(Int, Int)) {
  antennas
  |> list.combination_pairs
  |> list.fold(set.new(), fn(set, p) {
    let #(#(pos1, _), #(pos2, _)) = p
    let diff = #(pos2.0 - pos1.0, pos2.1 - pos1.1)
    // Too lazy to figure out how to loop here
    list.range(-50, 50)
    |> list.map(fn(i) { #(pos1.0 + i * diff.0, pos1.1 + i * diff.1) })
    |> list.filter(dict.has_key(grid, _))
    |> set.from_list
    |> set.union(set)
  })
}

pub fn pt_1(input: String) -> Int {
  let grid = make_grid(input)
  let antennas =
    grid
    |> dict.filter(fn(_, c) { c != "." })
    |> dict.to_list
    // Sort by antenna so we can chunk
    |> list.sort(fn(a1, a2) { string.compare(a1.1, a2.1) })
    |> list.chunk(pair.second)

  antennas
  |> list.map(get_antinodes)
  |> list.fold(set.new(), set.union)
  |> set.filter(dict.has_key(grid, _))
  |> set.size()
}

pub fn pt_2(input: String) -> Int {
  let grid = make_grid(input)
  let antennas =
    grid
    |> dict.filter(fn(_, c) { c != "." })
    |> dict.to_list
    // Sort by antenna so we can chunk
    |> list.sort(fn(a1, a2) { string.compare(a1.1, a2.1) })
    |> list.chunk(pair.second)

  antennas
  |> list.map(get_all_antinodes(_, grid))
  |> list.fold(set.new(), set.union)
  |> set.size()
}
