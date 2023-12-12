let parse_line line =
  let id =
    line |> String.split_on_char ':' |> List.hd |> String.split_on_char ' '
    |> (fun lst -> List.nth lst 1)
    |> int_of_string
  in
  let parse_cube cube =
    cube |> String.trim |> String.split_on_char ' ' |> fun lst ->
    (lst |> List.hd |> int_of_string, List.nth lst 1)
  in
  let parse_drawing drawing =
    drawing |> String.split_on_char ',' |> List.map parse_cube
  in
  let drawings =
    line |> String.split_on_char ':'
    |> (fun lst -> List.nth lst 1)
    |> String.split_on_char ';' |> List.map parse_drawing
  in
  (id, drawings)

let possible_drawing drawing =
  let get_count color =
    drawing |> List.filter (fun (_, c) -> color = c) |> fun lst ->
    if List.length lst = 0 then 0 else fst (List.hd lst)
  in
  let red_count = get_count "red" in
  let green_count = get_count "green" in
  let blue_count = get_count "blue" in
  red_count <= 12 && green_count <= 13 && blue_count <= 14

let run input =
  input |> List.map parse_line
  |> List.filter (fun (_, d) -> List.for_all possible_drawing d)
  |> List.map fst |> List.fold_left ( + ) 0 |> print_int
