let day_part = Sys.argv.(1) in
let day = String.sub day_part 0 (String.length day_part - 1) |> int_of_string in
let part = String.get day_part (String.length day_part - 1) in
let fname = "test/" ^ Sys.argv.(2) ^ ".txt" in
match (day, part) with
| 1, 'a' -> Advent.Day1a.run fname
| 1, 'b' -> Advent.Day1b.run fname
| _ -> failwith "Invalid day/part combination"
