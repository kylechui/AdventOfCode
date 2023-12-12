let get_calibration_value line =
  line |> String.to_seq
  |> Seq.filter (fun c -> c >= '0' && c <= '9')
  |> Seq.map (fun c -> Char.(code c - code '0'))
  |> List.of_seq
  |> fun lst -> (10 * List.hd lst) + List.(nth lst (length lst - 1))

let run fname =
  Parser.read_lines fname
  |> List.map get_calibration_value
  |> List.fold_left ( + ) 0 |> print_int
