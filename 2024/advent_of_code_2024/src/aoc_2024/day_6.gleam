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

type Direction {
  Left
  Up
  Down
  Right
}

fn turn(direction: Direction) -> Direction {
  case direction {
    Down -> Left
    Left -> Up
    Right -> Down
    Up -> Right
  }
}

fn move(pos: #(Int, Int), direction: Direction) -> #(Int, Int) {
  case direction {
    Down -> #(pos.0 + 1, pos.1)
    Left -> #(pos.0, pos.1 - 1)
    Right -> #(pos.0, pos.1 + 1)
    Up -> #(pos.0 - 1, pos.1)
  }
}

fn get_positions(
  grid: Dict(#(Int, Int), String),
  seen: Set(#(#(Int, Int), Direction)),
  pos: #(Int, Int),
  direction: Direction,
) -> Set(#(#(Int, Int), Direction)) {
  use <- bool.guard(when: set.contains(seen, #(pos, direction)), return: seen)
  let next_pos = move(pos, direction)

  case dict.get(grid, next_pos) {
    Error(Nil) -> set.insert(seen, #(pos, direction))
    Ok("#") -> get_positions(grid, seen, pos, turn(direction))
    Ok(_) ->
      get_positions(
        grid,
        set.insert(seen, #(pos, direction)),
        next_pos,
        direction,
      )
  }
}

fn has_cycle(
  grid: Dict(#(Int, Int), String),
  seen: Set(#(#(Int, Int), Direction)),
  pos: #(Int, Int),
  direction: Direction,
) -> Bool {
  use <- bool.guard(when: set.contains(seen, #(pos, direction)), return: True)

  let next_pos = move(pos, direction)
  case dict.get(grid, next_pos) {
    Error(Nil) -> False
    Ok("#") -> has_cycle(grid, seen, pos, turn(direction))
    Ok(_) ->
      has_cycle(grid, set.insert(seen, #(pos, direction)), next_pos, direction)
  }
}

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

pub fn pt_1(input: String) -> Int {
  let grid = make_grid(input)
  let assert Ok(#(pos, _)) =
    grid
    |> dict.filter(fn(_, value) { value == "^" })
    |> dict.to_list
    |> list.first

  get_positions(grid, set.new(), pos, Up) |> set.map(pair.first) |> set.size
}

pub fn pt_2(input: String) -> Int {
  let grid = make_grid(input)
  let assert Ok(#(pos, _)) =
    grid
    |> dict.filter(fn(_, value) { value == "^" })
    |> dict.to_list
    |> list.first

  grid
  |> dict.keys
  |> list.map(dict.insert(grid, _, "#"))
  |> list.count(has_cycle(_, set.new(), pos, Up))
}
