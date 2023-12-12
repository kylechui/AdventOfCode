let get_drawings line =
  let parse_cube cube =
    cube |> String.trim |> String.split_on_char ' ' |> fun lst ->
    (lst |> List.hd |> int_of_string, List.nth lst 1)
  in
  let parse_drawing drawing =
    drawing |> String.split_on_char ',' |> List.map parse_cube
  in
  line |> String.split_on_char ':'
  |> (fun lst -> List.nth lst 1)
  |> String.split_on_char ';' |> List.map parse_drawing

let get_count drawing color =
  drawing |> List.filter (fun (_, c) -> c = color) |> fun lst ->
  if List.length lst = 0 then 0 else fst (List.hd lst)

let run fname =
  Parser.read_lines fname |> List.map get_drawings
  |> List.map
       (List.fold_left
          (fun (r, g, b) drawing ->
            ( max r (get_count drawing "red"),
              max g (get_count drawing "green"),
              max b (get_count drawing "blue") ))
          (0, 0, 0))
  |> List.map (fun (r, g, b) -> r * g * b)
  |> List.fold_left ( + ) 0 |> print_int
