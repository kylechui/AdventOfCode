open Base

let get_nums line =
  let get_int_and_pos str start_idx end_idx =
    if start_idx = end_idx then ((0, 0), 0)
    else
      let len = end_idx - start_idx in
      let sub = String.sub str ~pos:start_idx ~len in
      ((start_idx, end_idx - 1), Int.of_string sub)
  in
  let rec get_nums' line start_idx cur_idx =
    if cur_idx = String.length line then
      [ get_int_and_pos line start_idx cur_idx ]
    else if not (Char.is_digit line.[cur_idx]) then
      get_int_and_pos line start_idx cur_idx
      :: get_nums' line (cur_idx + 1) (cur_idx + 1)
    else get_nums' line start_idx (cur_idx + 1)
  in
  get_nums' line 0 0

let my_print ((start_idx, end_idx), num) =
  Stdlib.print_int start_idx;
  Stdlib.print_char ',';
  Stdlib.print_int end_idx;
  Stdlib.print_string " -> ";
  Stdlib.print_int num;
  Stdlib.print_char '\n'

let run input =
  let nums =
    input |> List.map ~f:get_nums
    |> List.map ~f:(List.filter ~f:(fun (_, num) -> not (num = 0)))
  in
  let find_adjacent row col =
    let find_adjacent' row col =
      if
        row < 0 || col < 0
        || row >= List.length nums
        || col >= String.length (Stdlib.List.hd input)
      then []
      else
        List.filter (Stdlib.List.nth nums row)
          ~f:(fun ((start_idx, end_idx), _) ->
            start_idx <= col + 1 && col - 1 <= end_idx)
    in
    find_adjacent' (row - 1) col
    @ find_adjacent' row col
    @ find_adjacent' (row + 1) col
  in
  input
  |> List.mapi ~f:(fun row line ->
         String.foldi line ~init:[] ~f:(fun i acc c ->
             if not (Char.is_digit c || Char.equal c '.') then
               acc @ find_adjacent row i
             else acc))
  |> Stdlib.List.flatten
  |> List.dedup_and_sort ~compare:(fun x y -> if phys_equal x y then 0 else 1)
  |> List.fold_left ~init:0 ~f:(fun acc ((_, _), num) -> acc + num)
  |> Int.to_string |> Stdlib.print_endline
