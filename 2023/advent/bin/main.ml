let day_part = Sys.argv.(1) in
let day = String.sub day_part 0 (String.length day_part - 1) |> int_of_string in
let part = String.get day_part (String.length day_part - 1) in
let fname = "test/" ^ Sys.argv.(2) ^ ".txt" in
let input = Advent.Parser.read_lines fname in
match (day, part) with
| 1, 'a' -> Advent.Day1a.run input
| 1, 'b' -> Advent.Day1b.run input
| 2, 'a' -> Advent.Day2a.run input
| 2, 'b' -> Advent.Day2b.run input
| 3, 'a' -> Advent.Day3a.run input
| 3, 'b' -> Advent.Day3b.run input
| _ -> failwith "Invalid day/part combination"
