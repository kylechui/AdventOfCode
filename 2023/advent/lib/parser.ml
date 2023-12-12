let read_lines fname =
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
