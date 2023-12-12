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

let starts_with_num str =
  Hashtbl.fold
    (fun k v r ->
      match r with
      | None -> if String.starts_with ~prefix:k str then Some v else None
      | Some _ -> r)
    my_hash None

let ends_with_num str =
  Hashtbl.fold
    (fun k v r ->
      match r with
      | None -> if String.ends_with ~suffix:k str then Some v else None
      | Some _ -> r)
    my_hash None

let init str =
  if String.length str = 0 then "" else String.sub str 0 (String.length str - 1)

let tail str =
  if String.length str = 0 then "" else String.sub str 1 (String.length str - 1)

let rec get_first_dig = function
  | "" -> 0
  | str -> (
      match starts_with_num str with
      | Some num -> num
      | None -> get_first_dig (tail str))

let rec get_last_dig = function
  | "" -> 0
  | str -> (
      match ends_with_num str with
      | Some num -> num
      | None -> get_last_dig (init str))

let run input =
  input
  |> List.map (fun line ->
         let first_num = line |> get_first_dig in
         let last_num = line |> get_last_dig in
         (10 * first_num) + last_num)
  |> List.fold_left ( + ) 0 |> print_int
