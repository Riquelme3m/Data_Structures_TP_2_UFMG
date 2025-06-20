import matplotlib.pyplot as plt
import numpy as np
import math

# Data structure with nodes and execution times from resultados_armazens.csv
data = {
    20: [0.013025, 0.015650, 0.016655, 0.017011, 0.017169, 0.017269, 0.017715, 0.017724, 0.017903, 0.018108, 0.018473],
    100: [0.096772, 0.097185, 0.126116, 0.148269, 0.160216, 0.166337, 0.167881, 0.168767, 0.202806, 0.209244, 0.211750, 0.213172, 0.216114],
    200: [0.168065, 0.177332, 0.213966, 0.216627, 0.218637, 0.221224, 0.222146, 0.222783, 0.222940, 0.223109, 0.223465, 0.224025, 0.230005, 0.230960, 0.232780, 0.233470, 0.240119, 0.240852, 0.244332, 0.248845, 0.250700, 0.257761, 0.259531, 0.261232, 0.261779, 0.274266, 0.283058, 0.291842],
    300: [0.179468, 0.183299, 0.217487, 0.225951, 0.226213, 0.232837, 0.235044, 0.235570, 0.236067, 0.236183, 0.239113, 0.239531, 0.241283, 0.241756, 0.243067, 0.244365, 0.251859, 0.259031, 0.263208, 0.264290, 0.264706, 0.270593, 0.271557, 0.272873, 0.301075, 0.322087],
    400: [0.261494, 0.267307, 0.283263, 0.293304],
    500: [0.241910, 0.254386, 0.257395, 0.263877, 0.278576, 0.283120],
    600: [0.257885, 0.270065, 0.277075, 0.282931, 0.302509, 0.304040, 0.304863, 0.323672, 0.347909, 0.350646, 0.364857, 0.393084, 0.394510, 0.407202, 0.409674],
    700: [0.309714, 0.312275, 0.313091, 0.319406, 0.319506, 0.321216, 0.322481, 0.322557, 0.323742, 0.329684, 0.331980, 0.333522, 0.334894, 0.334954, 0.335298, 0.335933, 0.336022, 0.337960, 0.354672, 0.355183, 0.357317, 0.358225, 0.359295, 0.359668, 0.359800, 0.368446, 0.379343, 0.380989, 0.385545, 0.399435, 0.424167],
    800: [0.355312, 0.366416, 0.386206, 0.386260, 0.392153, 0.432949, 0.445201],
    900: [0.336445, 0.338374, 0.338710, 0.339288, 0.345241, 0.355527, 0.372590, 0.409078, 0.462948],
    1000: [0.417303, 0.419009, 0.432108, 0.434647, 0.437551, 0.438721, 0.441144, 0.476516, 0.480715, 0.484585, 0.487535, 0.501601]
}

def print_statistics():
    """Print comprehensive statistics"""
    print("=" * 80)
    print("ANÁLISE EXPERIMENTAL: ALGORITMO UNION-FIND")
    print("=" * 80)
    
    total_measurements = sum(len(times) for times in data.values())
    all_times = [t for times in data.values() for t in times]
    
    print(f"\nResumo Geral:")
    print(f"• Total de medições: {total_measurements}")
    print(f"• Range de armazéns: {min(data.keys())} - {max(data.keys())}")
    print(f"• Range de tempo: {min(all_times):.4f}s - {max(all_times):.4f}s")
    
    print(f"\n{'Armazéns':<10} {'Média':<10} {'Desvio':<10} {'Min':<10} {'Max':<10} {'Medições':<10}")
    print("-" * 70)
    
    node_counts = sorted(data.keys())
    means = []
    
    for nodes in node_counts:
        times = data[nodes]
        mean_val = np.mean(times)
        std_val = np.std(times)
        min_val = min(times)
        max_val = max(times)
        count = len(times)
        means.append(mean_val)
        
        print(f"{nodes:<10} {mean_val:<10.4f} {std_val:<10.4f} {min_val:<10.4f} {max_val:<10.4f} {count:<10}")
    
    # Complexity analysis
    if len(node_counts) >= 2:
        growth_ratio = means[-1] / means[0]
        node_ratio = node_counts[-1] / node_counts[0]
        complexity_factor = math.log(growth_ratio) / math.log(node_ratio)
        
        print(f"\nAnálise de Complexidade:")
        print(f"• Crescimento do tempo: {growth_ratio:.2f}x")
        print(f"• Crescimento dos nós: {node_ratio:.1f}x")
        print(f"• Fator de complexidade: O(n^{complexity_factor:.2f})")
        
        if complexity_factor < 1.2:
            print("• Classificação: Aproximadamente linear O(n)")
        elif complexity_factor < 1.8:
            print("• Classificação: Entre linear e quadrática")
        elif complexity_factor < 2.2:
            print("• Classificação: Aproximadamente quadrática O(n²)")
        else:
            print("• Classificação: Maior que quadrática")

def create_simple_graph():
    """Create a simple performance graph using matplotlib"""
    try:
        # Prepare data
        all_times = []
        all_nodes = []
        for nodes, times in data.items():
            all_times.extend(times)
            all_nodes.extend([nodes] * len(times))
        
        # Calculate means
        node_counts = sorted(data.keys())
        means = []
        stds = []
        
        for nodes in node_counts:
            times = data[nodes]
            means.append(np.mean(times))
            stds.append(np.std(times))
        
        # Create figure
        plt.figure(figsize=(12, 8))
        
        # Scatter plot
        plt.scatter(all_times, all_nodes, alpha=0.5, s=20, color='lightblue', label='Medições Individuais')
        
        # Mean with error bars
        plt.errorbar(means, node_counts, xerr=stds, fmt='ro', capsize=5, capthick=2, 
                    markersize=8, label='Média ± Desvio Padrão', color='red')
        
        # Trend line
        z = np.polyfit(means, node_counts, 1)
        p = np.poly1d(z)
        x_trend = np.linspace(min(means), max(means), 100)
        plt.plot(x_trend, p(x_trend), "r--", alpha=0.8, linewidth=2, 
                 label=f'Linha de Tendência')
        
        plt.xlabel('Tempo de Execução (segundos)', fontsize=12)
        plt.ylabel('Número de Armazéns', fontsize=12)
        plt.title('Tempo de Execução vs Número de Armazéns', fontsize=14, fontweight='bold')
        plt.grid(True, alpha=0.3)
        plt.legend()
        
        # Save the plot
        plt.savefig('analise_performance.png', dpi=300, bbox_inches='tight')
        print("\nGráfico salvo como 'analise_performance.png'")
        
        # Display the plot
        plt.show()
        
    except Exception as e:
        print(f"Erro ao criar gráfico: {e}")
        print("Matplotlib pode não estar disponível neste ambiente.")

# Execute the analysis
print("Iniciando análise de performance...")
print_statistics()

print("\nGerando gráfico...")
create_simple_graph()

print("\nAnálise completa!")
    plt.grid(True, alpha=0.3)
    plt.legend()
    
    # Performance per node
    plt.subplot(2, 2, 4)
    time_per_node = [means[i]/node_counts[i] for i in range(len(means))]
    plt.plot(node_counts, time_per_node, 'mo-', linewidth=2, markersize=8, 
             label='Tempo por Nó')
    plt.xlabel('Número de Armazéns')
    plt.ylabel('Tempo por Nó (s)')
    plt.title('Eficiência: Tempo por Armazém')
    plt.grid(True, alpha=0.3)
    plt.legend()
    
    plt.tight_layout()
    plt.savefig('analise_complexidade.png', dpi=300, bbox_inches='tight')
    plt.show()

def print_statistics():
    """Print comprehensive statistics"""
    print("=" * 80)
    print("ANÁLISE EXPERIMENTAL: ALGORITMO UNION-FIND")
    print("=" * 80)
    
    total_measurements = sum(len(times) for times in data.values())
    all_times = [t for times in data.values() for t in times]
    
    print(f"\nResumo Geral:")
    print(f"• Total de medições: {total_measurements}")
    print(f"• Range de armazéns: {min(data.keys())} - {max(data.keys())}")
    print(f"• Range de tempo: {min(all_times):.4f}s - {max(all_times):.4f}s")
    
    print(f"\n{'Armazéns':<10} {'Média':<10} {'Desvio':<10} {'Min':<10} {'Max':<10} {'Medições':<10}")
    print("-" * 70)
    
    node_counts = sorted(data.keys())
    means = []
    
    for nodes in node_counts:
        times = data[nodes]
        mean_val = np.mean(times)
        std_val = np.std(times)
        min_val = min(times)
        max_val = max(times)
        count = len(times)
        means.append(mean_val)
        
        print(f"{nodes:<10} {mean_val:<10.4f} {std_val:<10.4f} {min_val:<10.4f} {max_val:<10.4f} {count:<10}")
    
    # Complexity analysis
    if len(node_counts) >= 2:
        growth_ratio = means[-1] / means[0]
        node_ratio = node_counts[-1] / node_counts[0]
        complexity_factor = math.log(growth_ratio) / math.log(node_ratio)
        
        print(f"\nAnálise de Complexidade:")
        print(f"• Crescimento do tempo: {growth_ratio:.2f}x")
        print(f"• Crescimento dos nós: {node_ratio:.1f}x")
        print(f"• Fator de complexidade: O(n^{complexity_factor:.2f})")
        
        if complexity_factor < 1.2:
            print("• Classificação: Aproximadamente linear O(n)")
        elif complexity_factor < 1.8:
            print("• Classificação: Entre linear e quadrática")
        elif complexity_factor < 2.2:
            print("• Classificação: Aproximadamente quadrática O(n²)")
        else:
            print("• Classificação: Maior que quadrática")

if __name__ == "__main__":
    print("Gerando análise de performance...")
    print_statistics()
    create_performance_graph()
    
    print(f"\nArquivos gerados:")
    print(f"• analise_performance.png - Gráfico principal")
    print(f"• analise_complexidade.png - Análise de complexidade")
    print(f"\nPara instalar matplotlib: pip install matplotlib numpy")
    print(f"• Menor tempo médio: {min(means):.4f}s ({node_counts[means.index(min(means))]} armazéns)")
    print(f"• Maior tempo médio: {max(means):.4f}s ({node_counts[means.index(max(means))]} armazéns)")
    print(f"• Crescimento: {(means[-1]/means[0]):.2f}x do menor para o maior")
    
    # Calculate complexity trend
    if len(node_counts) >= 2:
        growth_ratio = means[-1] / means[0]
        node_ratio = node_counts[-1] / node_counts[0]
        complexity_factor = math.log(growth_ratio) / math.log(node_ratio)
        print(f"• Fator de complexidade estimado: O(n^{complexity_factor:.2f})")

def generate_csv_for_external_tools():
    """Generate clean CSV data for external plotting tools"""
    with open('clean_results.csv', 'w') as f:
        f.write("nodes,execution_time\n")
        for nodes, times in data.items():
            for time in times:
                f.write(f"{nodes},{time}\n")
    print(f"\nArquivo 'clean_results.csv' gerado para uso em ferramentas externas.")

if __name__ == "__main__":
    create_ascii_plot()
    generate_csv_for_external_tools()
    
    print(f"\nPara gráfico visual, use:")
    print(f"• Excel/LibreOffice Calc com clean_results.csv")
    print(f"• Online: plotly.com, chart.js, ou Google Sheets")
    print(f"• R: ggplot2")
