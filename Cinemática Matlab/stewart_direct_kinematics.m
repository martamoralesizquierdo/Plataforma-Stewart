function [x, y, z, A, B, C] = stewart_direct_kinematics(d, b, p)
    % Inicializar las variables
    x = 0; y = 0; z = 0; A = 0; B = 0; C = 0;

    % Calcular los ángulos de los actuadores
    theta = 2 * pi / 6 * (0:5);

    % Iterar hasta que la solución converja
    for iter = 1:100
        % Calcular las longitudes de los actuadores
        d_est = zeros(1, 6);
        for i = 1:6
            alpha = A + p / b * (cos(B) * sin(theta(i)) - sin(B) * cos(theta(i)) * cos(C));
            beta = B + p / b * cos(theta(i)) * sin(C);
            gamma = C + p / b * (sin(B) * sin(theta(i)) + cos(B) * cos(theta(i)) * cos(C));

            xi = x + b * cos(alpha) * sin(beta);
            yi = y + b * sin(alpha) * sin(beta);
            zi = z + b * cos(beta);

            dx = xi - p * cos(theta(i));
            dy = yi - p * sin(theta(i));
            dz = zi;

            d_est(i) = sqrt(dx^2 + dy^2 + dz^2);
        end

        % Calcular el error
        error = d - d_est;

        % Actualizar las variables
        x = x + 0.1 * mean(error);
        y = y + 0.1 * mean(error);
        z = z + 0.1 * mean(error);
        A = A + 0.1 * mean(error);
        B = B + 0.1 * mean(error);
        C = C + 0.1 * mean(error);

        % Comprobar la convergencia
        if max(abs(error)) < 1e-3
            break;
        end
    end
end
