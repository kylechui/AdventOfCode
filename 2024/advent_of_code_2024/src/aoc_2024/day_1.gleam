import gleam/dict
import gleam/int
import gleam/list
import gleam/option.{None, Some}
import gleam/string

pub fn pt_1(input: String) -> Int {
  let lines = string.split(input, on: "\n")
  let #(lst1, lst2) =
    lines
    |> list.map(fn(line) {
      let assert Ok(pair) = string.split_once(line, on: "   ")
      pair
    })
    |> list.map(fn(pair) {
      let #(str1, str2) = pair
      let assert Ok(num1) = int.parse(str1)
      let assert Ok(num2) = int.parse(str2)
      #(num1, num2)
    })
    |> list.unzip
  list.zip(list.sort(lst1, by: int.compare), list.sort(lst2, by: int.compare))
  |> list.map(fn(pair) {
    let #(num1, num2) = pair
    int.absolute_value(num1 - num2)
  })
  |> list.fold(0, int.add)
}

pub fn pt_2(input: String) -> Int {
  let lines = string.split(input, on: "\n")
  let #(lst1, lst2) =
    lines
    |> list.map(fn(line) {
      let assert Ok(pair) = string.split_once(line, on: "   ")
      pair
    })
    |> list.map(fn(pair) {
      let #(str1, str2) = pair
      let assert Ok(num1) = int.parse(str1)
      let assert Ok(num2) = int.parse(str2)
      #(num1, num2)
    })
    |> list.unzip
  let freq =
    list.fold(lst2, dict.new(), fn(freq, num) {
      dict.upsert(freq, num, fn(opt) {
        case opt {
          None -> 1
          Some(f) -> f + 1
        }
      })
    })
  list.fold(lst1, 0, fn(sum, num) {
    case dict.get(freq, num) {
      Error(Nil) -> sum
      Ok(count) -> sum + num * count
    }
  })
}
