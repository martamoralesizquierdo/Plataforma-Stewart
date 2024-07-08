%% Ejemplo de uso: Visualización de las longitudes de las patas de la
% plataforma para obtener la orientación requerida

% Definir los parámetros de la plataforma
r_base = 23; % Radio del hexágono de la base en cm
r_plat = 23; % Radio del hexágono de la plataforma en cm
height_plat = 30; % Altura de la plataforma en cm

% Definir los puntos de anclaje
[B, P] = define_anchor_points(r_base, r_plat, height_plat);
disp('Puntos de anclaje en la base (B):');
disp(B);
disp('Puntos de anclaje en la plataforma (P):');
disp(P);

% Definir la posición y orientación de la plataforma que queremos obtener
x = 0;
y = 3;
z = 2; % La plataforma está a la altura de los actuadores desde la base
%Tom
roll = 0;
pitch = 0;
yaw = 0.5;

% Calcular las longitudes de los actuadores usando la función de cinemática inversa
d = stewart_inverse_kinematics1(x, y, z, roll, pitch, yaw, B, P);
disp('Longitudes de los actuadores:');
disp(d);

figure
bar(d,0.4,'b')
xlabel 'Actuador'
ylabel 'Longitud de los actuadores[cm]'
% Agregar texto con las longitudes de los actuadores sobre cada barra
for i = 1:length(d)
    text(i, d(i), sprintf('%.2f', d(i)),'HorizontalAlignment', 'center', 'VerticalAlignment', 'bottom')
end
% Agregar texto con los valores de x, y, z, yaw, pitch y roll en la figura
text(0.5, max(d)*1.1, sprintf('x = %.2f, y = %.2f, z = %.2f, yaw = %.2f, pitch = %.2f, roll = %.2f', x, y, z, yaw, pitch, roll), ...
    'HorizontalAlignment', 'center', ...
    'VerticalAlignment', 'bottom')

