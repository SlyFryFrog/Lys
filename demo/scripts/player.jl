module Player
push!(LOAD_PATH, "../../src/core/scripting/julia/bindings/lys.jl")
using ..Lys

node = Lys.Node()  # calls the C++ default constructor
println(typeof(node))

println("Hello from Julia")
Lys.set_name(node, "Fabien")
println(Lys.get_name(node))

# function term()::Cvoid
#     println("Hello from julia!")
#     init(node)
#     Lys.set_name(node, "Fabien")
#     println(Lys.get_name(node));
# end

# function init(self::Lys.Node)::Cvoid
#     println(typeof(self))
    
#     # name = get_name(self)          # calls get_name, returns string
#     # println(name)
#     # self.set_name("Alice")          # calls set_name, sets m_name
# end

# function process(self::Lys.Node, delta::Float64)::Cvoid
#     println(delta)
# end
end