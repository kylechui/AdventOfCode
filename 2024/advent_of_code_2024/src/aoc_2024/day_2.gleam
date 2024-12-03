import gleam/bool
import gleam/int
import gleam/io
import gleam/list
import gleam/string

type State {
  SafeDecreasing
  SafeIncreasing
  Unsafe
}

fn diff_to_state(diff: Int) -> State {
  case diff {
    _ if diff > 3 || diff < -3 || diff == 0 -> Unsafe
    _ if diff > 0 -> SafeIncreasing
    _ -> SafeDecreasing
  }
}

fn safe1(report: List(Int)) -> Bool {
  let states =
    list.window_by_2(report)
    |> list.map(fn(pair) {
      let #(cur, next) = pair
      diff_to_state(next - cur)
    })
  let assert Ok(first_state) = list.first(states)
  first_state != Unsafe && list.all(states, fn(state) { first_state == state })
}

fn safe2(report: List(Int)) -> Bool {
  report
  |> list.index_map(fn(_, idx) {
    list.append(list.take(report, idx), list.drop(report, idx + 1))
  })
  |> list.map(fn(hi) {
    io.println(hi |> list.map(int.to_string) |> string.join(", "))
    hi
  })
  |> list.any(safe1)
}

pub fn pt_1(input: String) -> Int {
  input
  |> string.split(on: "\n")
  |> list.map(string.split(_, on: " "))
  |> list.map(list.map(_, fn(num) {
    let assert Ok(n) = int.parse(num)
    n
  }))
  |> list.count(safe1)
}

pub fn pt_2(input: String) -> Int {
  input
  |> string.split(on: "\n")
  |> list.map(string.split(_, on: " "))
  |> list.map(list.map(_, fn(num) {
    let assert Ok(n) = int.parse(num)
    n
  }))
  |> list.count(safe2)
}
