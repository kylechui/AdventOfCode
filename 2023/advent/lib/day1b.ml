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

let my_hash = Hashtbl.create 20

let () =
  Hashtbl.add my_hash "zero" 0;
  Hashtbl.add my_hash "0" 0;
  Hashtbl.add my_hash "one" 1;
  Hashtbl.add my_hash "1" 1;
  Hashtbl.add my_hash "two" 2;
  Hashtbl.add my_hash "2" 2;
  Hashtbl.add my_hash "three" 3;
  Hashtbl.add my_hash "3" 3;
  Hashtbl.add my_hash "four" 4;
  Hashtbl.add my_hash "4" 4;
  Hashtbl.add my_hash "five" 5;
  Hashtbl.add my_hash "5" 5;
  Hashtbl.add my_hash "six" 6;
  Hashtbl.add my_hash "6" 6;
  Hashtbl.add my_hash "seven" 7;
  Hashtbl.add my_hash "7" 7;
  Hashtbl.add my_hash "eight" 8;
  Hashtbl.add my_hash "8" 8;
  Hashtbl.add my_hash "nine" 9;
  Hashtbl.add my_hash "9" 9

let contains_at_index str index sub =
  let sub_len = String.length sub in
  let str_len = String.length str in
  if index + sub_len > str_len then false
  else String.sub str index sub_len = sub

let contains_num_at_index str index =
  Hashtbl.fold
    (fun k v r ->
      match r with
      | None -> if contains_at_index str index k then Some v else None
      | Some _ -> r)
    my_hash None

let get_first_dig s =
  let rec get_first_dig' str index =
    match contains_num_at_index str index with
    | Some num -> num
    | None -> get_first_dig' str (index + 1)
  in
  get_first_dig' s 0

let get_last_dig s =
  let rec get_last_dig' str index =
    match contains_num_at_index str index with
    | Some num -> num
    | None -> get_last_dig' str (index - 1)
  in
  get_last_dig' s (String.length s - 1)

let run fname =
  lines fname
  |> List.map (fun line ->
         let first_num = line |> get_first_dig in
         let last_num = line |> get_last_dig in
         (10 * first_num) + last_num)
  |> List.fold_left ( + ) 0 |> print_int
