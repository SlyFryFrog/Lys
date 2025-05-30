module Player
push!(LOAD_PATH, "../../src/core/scripting/julia/bindings/lys.jl")
using ..Lys

mutable struct Character
    parent::Lys.Node
    position::NTuple{3,Float32}
    speed::Float32
end

Character() = Character(Lys.Node(), (0f0, 0f0, 0f0), 1.0f0)
global node::Union{Character,Nothing} = nothing

# Define global state of Character
function on_ready()
    global node = Character()
end

function process(delta::Float64)::Cvoid
    Lys.set_name(node.parent, "Fabien")
    println(Lys.get_name(node.parent))
    println("Processing with delta=", delta)
end

function process_inputs()

end

end
