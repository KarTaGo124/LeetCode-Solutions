class Solution
{
public:
	long long sumScores(string s)
	{
		int n = s.length();		   // Obtenemos la longitud de la cadena
		vector<int> Z(n, 0);	   // Inicializamos el array Z con ceros
		long long total_score = 0; // Variable para almacenar la suma total de los puntajes

		int L = 0, R = 0; // L y R son los punteros que definen el intervalo de la "ventana"

		// Empezamos a calcular el array Z desde la posición 1
		for (int i = 1; i < n; i++)
		{
			// Si i está dentro del intervalo [L, R], usamos el valor de Z[k]
			if (i <= R)
			{
				int k = i - L; // Calculamos el índice dentro de la ventana
				// Si Z[k] es menor que la longitud de la ventana, usamos el valor de Z[k]
				if (Z[k] < R - i + 1)
				{
					Z[i] = Z[k];
				}
				else
				{
					// Si no, necesitamos expandir la ventana
					L = i; // Actualizamos L a la posición actual
					// Comparamos los caracteres mientras sean iguales
					while (R < n && s[R] == s[R - L])
					{
						R++; // Extendemos la ventana hacia la derecha
					}
					Z[i] = R - L; // Asignamos la longitud del prefijo coincidente
					R--;		  // Retrocedemos R para no contar el último carácter comparado
				}
			}
			else
			{
				// Si i no está en la ventana [L, R], comenzamos a comparar desde i
				L = R = i; // Establecemos los nuevos límites de la ventana
				// Comparamos los caracteres mientras sean iguales
				while (R < n && s[R] == s[R - L])
				{
					R++; // Extendemos la ventana hacia la derecha
				}
				Z[i] = R - L; // Asignamos la longitud del prefijo coincidente
				R--;		  // Retrocedemos R después de la comparación
			}
		}

		// Sumamos los puntajes de todos los prefijos (valores de Z)
		for (int i = 0; i < n; i++)
		{
			total_score += Z[i]; // Sumamos el valor de Z[i] a la suma total
		}

		// Añadimos el puntaje del primer prefijo, que es igual a la longitud de la cadena completa
		total_score += n; // El primer prefijo tiene un puntaje igual a la longitud de la cadena

		return total_score; // Retornamos la suma total de los puntajes
	}
};
