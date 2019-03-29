-- Tup build file

local debug, release = 0, 1
local linux, windows, other = 0, 1, 2
local executable, static_library, shared_library = 0, 1, 2

operating_system = linux

build_mode = debug

build_type = static_library

output     = "labcutils"

build_dir  = "build/"
obj_dir    = build_dir .. "obj/"
bin_dir    = build_dir .. "bin/"

src            = {
    "src/lab/logger.c",
    "src/lab/memory.c",
    "src/lab/vector.c",
    "src/lab/arg_parser.c",
}
include_dirs   = {
    "src",
}
lib_paths      = {
}
link_libraries = {
}

defines = {
    "LAB_64_BIT"
}

compiler = "gcc"
linker   = "gcc"

compile_args = " -std=c11 -m64 "
link_args    = " -std=c11 -m64 "

if build_mode == release then

    compile_args = compile_args .. " -O3 -flto "
    link_args    = link_args    .. " -O3 -flto "

    defines[#defines + 1] = "LAB_BUILD_RELEASE"

elseif build_mode == debug then

    compile_args = compile_args .. " -O0 -g -Wall "
    link_args    = link_args    .. " -O0 -g -Wall "

    defines[#defines + 1] = "LAB_BUILD_DEBUG"

end

if operating_system == linux then

elseif operating_system == windows then 

end



-- Magic happens below this comment



build_include_dir_str = ""
for i = 1, #include_dirs do
    build_include_dir_str = build_include_dir_str .. " -I" .. include_dirs[i]
end

build_defines_str = ""
for i = 1, #defines do
    build_defines_str = build_defines_str .. " -D" .. defines[i]
end

link_link_paths_str = ""
for i = 1, #lib_paths do 
    link_link_paths_str = link_link_paths_str .. " -L".. lib_paths[i] 
end

link_link_libs_str = ""
for i = 1, #link_libraries do 
    link_link_libs_str = link_link_libs_str .. " -l".. link_libraries[i] 
end

build_command = compiler .. " -c " .. compile_args.. build_include_dir_str .. build_defines_str .. " -o %o %f"
link_command  = linker   .. link_args .. link_link_paths_str   .. link_link_libs_str .. " -o %o %f"

objects = tup.foreach_rule(
    src,
    build_command,
    { obj_dir .. "%B.o" }
)

if build_type == executable then

    tup.rule(objects, link_command, { bin_dir .. output })

elseif build_type == static_library then

    tup.rule(objects, "ar rcs  %o %f", { bin_dir .. "lib" .. output .. ".a" })

end


-- Example

tup.rule(
    { "example/example.c" },
    compiler .. " -o %o -c %f -Isrc",
    { "example/build/obj/%B.o" }
)

tup.rule(
    { "example/build/obj/example.o", bin_dir .. "lib" .. output .. ".a" },
    linker .. " -o %o example/build/obj/example.o -Lbuild/bin -llabcutils",
    { "example/build/bin/example" }
)