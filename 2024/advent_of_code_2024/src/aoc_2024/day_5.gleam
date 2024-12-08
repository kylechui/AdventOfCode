import gleam/bool
import gleam/dict
import gleam/function
import gleam/int
import gleam/io
import gleam/list
import gleam/order.{Eq, Gt, Lt}
import gleam/pair
import gleam/string

fn parse_int(str: String) -> Int {
  let assert Ok(num) = int.parse(str)
  num
}

fn valid_update(update: List(Int), rules: List(#(Int, Int))) -> Bool {
  let idx_map = update |> list.index_map(fn(x, i) { #(x, i) }) |> dict.from_list
  rules
  |> list.all(fn(rule) {
    case dict.get(idx_map, rule.0), dict.get(idx_map, rule.1) {
      Error(Nil), _ -> True
      _, Error(Nil) -> True
      Ok(idx1), Ok(idx2) -> idx1 < idx2
    }
  })
}

fn sort_update(update: List(Int), rules: List(#(Int, Int))) -> List(Int) {
  let rules_map =
    rules
    |> list.map(fn(rule) { [#(rule, Lt), #(#(rule.1, rule.0), Gt)] })
    |> list.flatten
    |> dict.from_list
  update
  |> list.sort(fn(pg1, pg2) {
    case dict.get(rules_map, #(pg1, pg2)) {
      Error(Nil) -> Eq
      Ok(cmp) -> cmp
    }
  })
}

pub fn pt_1(input: String) -> Int {
  let assert Ok(#(ordering_rules_raw, updates_raw)) =
    string.split_once(input, on: "\n\n")
  let ordering_rules =
    ordering_rules_raw
    |> string.split(on: "\n")
    |> list.map(fn(line) {
      let assert Ok(#(str1, str2)) = string.split_once(line, on: "|")
      #(parse_int(str1), parse_int(str2))
    })
  let updates =
    updates_raw
    |> string.split(on: "\n")
    |> list.map(string.split(_, on: ","))
    |> list.map(list.map(_, parse_int))
  let valid_updates = updates |> list.filter(valid_update(_, ordering_rules))
  valid_updates
  |> list.map(fn(update) {
    let assert Ok(idx) = update |> list.length |> int.divide(2)
    let assert Ok(middle) = update |> list.drop(idx) |> list.first
    middle
  })
  |> int.sum
}

pub fn pt_2(input: String) -> Int {
  let assert Ok(#(ordering_rules_raw, updates_raw)) =
    string.split_once(input, on: "\n\n")
  let ordering_rules =
    ordering_rules_raw
    |> string.split(on: "\n")
    |> list.map(fn(line) {
      let assert Ok(#(str1, str2)) = string.split_once(line, on: "|")
      #(parse_int(str1), parse_int(str2))
    })
  let updates =
    updates_raw
    |> string.split(on: "\n")
    |> list.map(string.split(_, on: ","))
    |> list.map(list.map(_, parse_int))
  let invalid_updates =
    updates |> list.filter(fn(update) { !valid_update(update, ordering_rules) })
  invalid_updates
  |> list.map(sort_update(_, ordering_rules))
  |> list.map(fn(update) {
    let assert Ok(idx) = update |> list.length |> int.divide(2)
    let assert Ok(middle) = update |> list.drop(idx) |> list.first
    middle
  })
  |> int.sum
}
