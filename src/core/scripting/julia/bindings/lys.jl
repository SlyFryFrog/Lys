module Lys
using CxxWrap

@wrapmodule(() -> "/Users/marcus/dev/Lys/out/build/Debug/libLys", :define_lys_module)

function __init__()
    @initcxx
end

end