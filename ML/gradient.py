def f(x): 
    return (2*x + 3)**2
def df(x): 
    return 2 * (2* x + 3) * 2 

def gradient_descent(starting_point, learning_rate, tolerance=1e-6, max_iterations=1000):
    x = starting_point
    for i in range(max_iterations):
        grad = df(x)
        x_new = x - learning_rate * grad
        if abs(x_new - x) < tolerance:
            break
        x = x_new
    return x

local_min = gradient_descent(starting_point=2, learning_rate=0.1)
print(f"Minimum at x = {local_min:.6f}, y = {f(local_min):.6f}")
