import gleam/bool
import gleam/int
import gleam/list
import gleam/option.{Some}
import gleam/regexp

pub fn pt_1(input: String) -> Int {
  let assert Ok(r) =
    regexp.compile("mul\\((\\d+),(\\d+)\\)", regexp.Options(False, False))

  regexp.scan(r, input)
  |> list.map(fn(match) {
    let assert [Some(m1), Some(m2)] = match.submatches
    let assert Ok(n1) = int.parse(m1)
    let assert Ok(n2) = int.parse(m2)
    n1 * n2
  })
  |> int.sum
}

pub fn pt_2(input: String) -> Int {
  let assert Ok(r) =
    regexp.compile(
      "mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)",
      regexp.Options(False, False),
    )

  {
    regexp.scan(r, input)
    |> list.fold(#(0, True), fn(acc, match) {
      case match.content {
        "do()" -> #(acc.0, True)
        "don't()" -> #(acc.0, False)
        _ -> {
          use <- bool.guard(when: !acc.1, return: acc)
          let assert [Some(m1), Some(m2)] = match.submatches
          let assert Ok(n1) = int.parse(m1)
          let assert Ok(n2) = int.parse(m2)
          #(acc.0 + n1 * n2, True)
        }
      }
    })
  }.0
}
