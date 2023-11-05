#. Apply your solver to the dam-break setup and play around with different sets of initial water heights :math:`h_l` and :math:`h_r`.
   What do you observe? How large is the impact of the particle velocity :math:`u_r` in the river?

  If the water in behind the dam is higher than the river it creates a shock wave, that floods the river. The higher the water the higher
  created shockwave. When the water is lower than the river a rare wave is created moving in the direction of the river. The faster the water
  in the river is, the faster will the created shock or rare wave travel along the river.

#. Assume a water reservoir of unlimited size and a village 25 km downstream with initial values :math:`q_l=[14, 0]^T` and :math:`q_r=[3.5, 0.7]^T`.
   How much time do you have to evacuate the village in our model before the shock wave arrives?

  Since simulating the whole travel of the shock wave would take longer than 1.25 of simulation time, we downscaled every length by 10. This
  would decrease the accuracy but make the problem calculatable.
  
  We set up the finite volume solver as following: we have a reservoir with the height of :math:`1.4 \frac{m}{10}` a river height of :math:`0.37 \frac{m}{10}` and a distance to the village of :math:`2500 \frac{m}{10}`. The river has a momentum of 
  :math:`0.07 kg\frac{m}{10s}`

  After letting the simulation run for 2300 seconds the shock wave traveled for :math:`1100 \frac{m}{10}` in the direction of the village. 
  If the wave travels on with the same speed, it reaches the village after 5227 seconds. Calculated to hours, we have 1.45 hours to evacuate 
  the village. 

  
