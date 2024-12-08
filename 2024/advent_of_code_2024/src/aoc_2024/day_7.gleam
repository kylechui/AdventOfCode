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

fn parse_line(line: String) -> #(Int, List(Int)) {
  let assert Ok(#(goal_raw, values_raw)) = string.split_once(line, on: ": ")
  let goal = parse_int(goal_raw)
  let values = values_raw |> string.split(on: " ") |> list.map(parse_int)
  #(goal, values)
}

fn can_combine(goal: Int, values: List(Int)) -> Bool {
  let assert [first, ..rest] = values
  can_combine_helper(goal, rest, first)
}

fn can_combine_helper(goal: Int, values: List(Int), cur: Int) -> Bool {
  use <- bool.guard(when: cur > goal, return: False)
  case values {
    [] -> cur == goal
    [first, ..rest] ->
      can_combine_helper(goal, rest, cur + first)
      || can_combine_helper(goal, rest, cur * first)
  }
}

fn can_combine2(goal: Int, values: List(Int)) -> Bool {
  let assert [first, ..rest] = values
  can_combine_helper2(goal, rest, first)
}

fn can_combine_helper2(goal: Int, values: List(Int), cur: Int) -> Bool {
  use <- bool.guard(when: cur > goal, return: False)
  case values {
    [] -> cur == goal
    [first, ..rest] ->
      can_combine_helper2(goal, rest, cur + first)
      || can_combine_helper2(goal, rest, cur * first)
      || can_combine_helper2(
        goal,
        rest,
        parse_int(int.to_string(cur) <> int.to_string(first)),
      )
  }
}

pub fn pt_1(input: String) -> Int {
  input
  |> string.split(on: "\n")
  |> list.map(parse_line)
  |> list.filter(fn(problem) { can_combine(problem.0, problem.1) })
  |> list.map(pair.first)
  |> int.sum
}

pub fn pt_2(input: String) -> Int {
  input
  |> string.split(on: "\n")
  |> list.map(parse_line)
  |> list.filter(fn(problem) { can_combine2(problem.0, problem.1) })
  |> list.map(pair.first)
  |> int.sum
}
