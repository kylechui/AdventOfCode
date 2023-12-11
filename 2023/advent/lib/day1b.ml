let lines fname =
  let channel = open_in fname in
  try
    let rec read_list' acc =
      try
        let line = input_line channel in
        read_list' (line :: acc)
      with End_of_file -> List.rev acc
    in
    read_list' []
  with Sys_error err ->
    print_endline ("Error: " ^ err);
    []

let is_digit c = c >= '0' && c <= '9'

let get_first_dig =
  let get_first_dig' =
    String.fold_left (fun acc c ->
        if is_digit acc || not (is_digit c) then acc else c)
  in
  get_first_dig' ' '

let get_last_dig =
  let get_last_dig' =
    String.fold_right (fun c acc ->
        if is_digit acc || not (is_digit c) then acc else c)
  in
  fun line -> get_last_dig' line ' '

let run fname =
  lines fname
  |> List.map (fun line ->
         let first_num =
           line |> get_first_dig |> int_of_char
           |> Fun.flip ( - ) (Char.code '0')
         in
         let last_num =
           line |> get_last_dig |> int_of_char |> Fun.flip ( - ) (Char.code '0')
         in
         (10 * first_num) + last_num)
  |> List.fold_left ( + ) 0 |> print_int
