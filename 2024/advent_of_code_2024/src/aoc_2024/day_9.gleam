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

fn parse_int(str: String) -> Int {
  let assert Ok(num) = int.parse(str)
  num
}

fn every_other(lst: List(a)) -> List(a) {
  case lst {
    [] | [_] -> lst
    [first, _, ..rest] -> [first, ..every_other(rest)]
  }
}

fn get_checksum(
  file_indices: Dict(Int, Int),
  end_range: List(#(Int, Int)),
  index: Int,
  max_index: Int,
  sum: Int,
) -> Int {
  use <- bool.guard(when: index == max_index, return: sum)
  case dict.get(file_indices, index) {
    Error(Nil) ->
      case end_range {
        [] -> panic
        [#(value, 1), ..rest] ->
          get_checksum(
            file_indices,
            rest,
            index + 1,
            max_index,
            sum + index * value,
          )
        [#(value, count), ..rest] ->
          get_checksum(
            file_indices,
            [#(value, count - 1), ..rest],
            index + 1,
            max_index,
            sum + index * value,
          )
      }
    Ok(value) ->
      get_checksum(
        file_indices,
        end_range,
        index + 1,
        max_index,
        sum + index * value,
      )
  }
}

pub fn pt_1(input: String) -> Int {
  let disk_map = input |> string.to_graphemes |> list.map(parse_int)
  let file_indices =
    disk_map
    |> list.scan(from: 0, with: int.add)
    |> list.prepend(0)
    |> list.window_by_2
    |> every_other
    |> list.index_map(fn(range, idx) {
      list.range(range.0, range.1 - 1) |> list.map(pair.new(_, idx))
    })
    |> list.flatten
    |> dict.from_list
  // TODO: Name this better
  let end_range =
    disk_map
    |> every_other
    |> list.index_map(fn(x, i) { #(i, x) })
    |> list.reverse
  let num_blocks = disk_map |> every_other |> int.sum
  get_checksum(file_indices, end_range, 0, num_blocks, 0)
}

fn replace(lst: List(a), from: a, to: List(a)) -> List(a) {
  let #(prefix, suffix) = list.split_while(lst, fn(ahh) { ahh != from })
  list.flatten([prefix, to, list.drop(suffix, 1)])
}

// start, length, value
fn move(lst: List(#(Int, Int, Int)), val: Int) -> List(#(Int, Int, Int)) {
  use <- bool.guard(when: val == 0, return: lst)
  let assert Ok(to_move) =
    list.filter(lst, fn(tup) { tup.2 == val }) |> list.first
  let free_spaces = list.filter(lst, fn(tup) { tup.2 == 0 })
  case list.find(free_spaces, fn(free) { free.1 >= to_move.1 }) {
    Error(Nil) -> lst
    Ok(free) if free.0 >= to_move.0 -> lst
    Ok(free) if free.1 == to_move.1 ->
      replace(lst, free, [#(free.0, to_move.1, to_move.2)])
      |> list.filter(fn(tup) { tup != to_move })
    Ok(free) ->
      replace(lst, free, [
        #(free.0, to_move.1, to_move.2),
        #(free.0 + to_move.1, free.1 - to_move.1, 0),
      ])
      |> list.filter(fn(tup) { tup != to_move })
  }
}

pub fn pt_2(input: String) -> Int {
  let disk_map = input |> string.to_graphemes |> list.map(parse_int)
  // need to map to start position, length, and value
  let file_indices =
    [0, ..list.scan(over: disk_map, from: 0, with: int.add)]
    |> list.index_map(fn(x, i) {
      case int.is_odd(i) {
        False -> #(x, i / 2)
        True -> #(x, 0)
      }
    })
  let blocks =
    list.window_by_2(file_indices)
    |> list.map(fn(e) { #(e.0.0, e.1.0 - e.0.0, e.0.1) })
    |> list.drop(1)
  let val = list.length(blocks) / 2
  list.fold(list.range(1, val) |> list.reverse, blocks, move)
  |> list.filter(fn(tup) { tup.2 != 0 })
  |> list.fold(0, fn(sum, tup) {
    let cur_checksum = { 2 * tup.0 + tup.1 - 1 } * tup.1 * tup.2 / 2
    sum + cur_checksum
  })
}
