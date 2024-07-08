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
y = 0;
z = 10; % La plataforma está a la altura de los actuadores desde la base
%Tom
roll = 0;
pitch = 0;
yaw = 0;

% Calcular las longitudes de los actuadores usando la función de cinemática inversa
d = stewart_inverse_kinematics1(x, y, z, roll, pitch, yaw, B, P);
disp('Longitudes de los actuadores:');
disp(d);

figure
bar(d,0.4,'b')
xlabel Patas
ylabel 'Longitud de las patas'
