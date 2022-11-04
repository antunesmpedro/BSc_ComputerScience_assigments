import random
import math
import scipy.stats
import time
import sys
start_time = time.time()



def new_packages(f1, i, locker_status):
	# novos packages

	n_packages = random.randint(10,50)
	print(f"|{i+1:^5}|{n_packages:^7}|", file=f1, end = " ")
	delivers_prob = [0.5, 0.5]
	packages = {j:0 for j in [1, 2]} # 1-home ; 2-locker

	for j in range(n_packages):
		r = random.random()
		if r <= .5:
			packages[1] += 1

		else:
			packages[2] += 1

	print(f"{packages[1]:^6}|", file=f1, end = " ") #home: 
	print(f"{packages[2]:^6}|", file=f1, end = " ") #locker

	return f1, packages, locker_status



def day_deliveries_func(f1, recipient_prob, locker_status, c, compensation_prob, i):
	# realizar as entregas (sem contar com o primeiro dia i=0)

	day_deliveries = {k:0 for k in [1, 2, 3]} # 1-pf ; 2-oc ; 3-lckr

	if i > 0:
		for j in range(locker_status[2]):		
			# probabilidade de estar ou não o package para o destinatário
			if random.random() <= recipient_prob:
				day_deliveries[3] += 1
				# probabilidade do destinatário ser OC
				#print(f"locker_status_home:{locker_status[1]}")
				if locker_status[1] > day_deliveries[2] and random.random() <= compensation_prob[c]:	
					day_deliveries[2] += 1

		# caso ainda haja packets para entregar em casa, chamar pf	
		if locker_status[1] > day_deliveries[2]:
			day_deliveries[1] = locker_status[1] - day_deliveries[2]

	print(f"{day_deliveries[1]:^4}|", file=f1, end = " ")	#entregas pf por dia
	print(f"{day_deliveries[2]:^4}|", file=f1, end = " ")	#entregas oc por dia
	print(f"{day_deliveries[3]:^5}|", file=f1, end = " ")	#entreegas lckr por dia

	return f1, day_deliveries



def update_locker(f1, locker_status, day_deliver, accumulated_deliveries, c, compensation_oc, pf_cost_gt10, i, packages):
	# atualizar o cacifo e o custo

	pf_day_cost = 0
	oc_day_cost = 0

	if i > 0:
		locker_status[1] -= day_deliver[1] + day_deliver[2]
		locker_status[2] -= day_deliver[3]

		accumulated_deliveries[1] += day_deliver[1];
		accumulated_deliveries[2] += day_deliver[2];
		accumulated_deliveries[3] += day_deliver[3];	

		if day_deliver[1] <= 10:
			pf_day_cost = day_deliver[1]
		else:
			pf_day_cost = (day_deliver[1]-10)*pf_cost_gt10 + 10
		
		oc_day_cost = day_deliver[2] * compensation_oc[c]

	# pacotes para o dia seguinte	
	locker_status[1] += packages[1]
	locker_status[2] += packages[2]	

	print(f"{accumulated_deliveries[1]:^6}|", file=f1, end = " ") # pf acc deliveries
	print(f"{accumulated_deliveries[2]:^6}|", file=f1, end = " ") # oc acc deliveries
	print(f"{accumulated_deliveries[3]:^7}|", file=f1, end = " ") # lckr acc deliveries

	print(f"{float(pf_day_cost):^7.2f}|", file=f1, end = " ") # pf day cost
	print(f"{oc_day_cost:^7.2f}|", file=f1, end = " ") # oc day cost

	return f1, locker_status, accumulated_deliveries, pf_day_cost, oc_day_cost



def mean_confidence_interval(data, alpha):
	# calcular intervalo de valor da simulação

	n = len(data)
	m = 0
	for i in range(n):
		m += data[i]

	m = float(m/n)	

	var = 0
	for i in range(n):
		var += (data[i]-m)**2

	var = float(var/(n-1))

	# calls the inverse CDF of the Student's t distribution
	# tfact = 2.57632109586
	tfact = scipy.stats.t._ppf(1-alpha/2., (n-1))
	h = tfact * math.sqrt((var/n))
	#print(f"\n H: {h} | n: {n} | tfact: {tfact} | var: {var} | M: {m}")
	return m-h, m+h



def simulation():
	compensation_oc = 	[ 0.0, 	0.5, 1.0, 1.5, 	1.8]
	compensation_prob = [0.01, 0.25, 0.5, 0.6, 0.75]
	days = 120
	recipient_prob = 0.75
	ic = 0.99
	alpha = 1 - ic
	pf_cost_gt10 = 2
	observations = 10000
	val_cost = [[0 for x in range(2)] for y in range(5)]
	val_packs = [[0 for x in range(2)] for y in range(5)]
	accumulated_deliveries = {i:0 for i in [1, 2, 3]} # 1-pf ; 2-oc ; 3-lckr


	# redirecionar o output para os ficheiros f1 e f2
	f1 = open('simulation.sol','w')
	f2 = open('stats.sol','w')

	print(f"|-----------------------------------------------------------------------------------------------------|", file=f2)
	print(f"|                                                                                                     |", file=f2)
	print(f"|                                        STATISTICAL ANALYSIS                                         |",file=f2)
	print(f"|                                                                                                     |", file=f2)
	print(f"|-----------------------------------------------------------------------------------------------------|", file=f2)
	print(f"|  COMPENSATION   |{'COST':^41}|{'PACKAGES':^41}|",file=f2)
	print(f"|-----------------------------------------------------------------------------------------------------|", file=f2)

	# simular as entregas para cada compensacao
	for c in range(len(compensation_oc)):
		data_cost = {i:0 for i in range(observations)}
		data_packages = {i:0 for i in range(observations)}


		# fazer as observacoes para a analise estatistica
		for k in range(observations):
			print(f"|------------------------------------------------------------------------------------------------------------------------|", file=f1)
			print(f"|                                                                                                                        |", file=f1)
			print(f"|                                                     OBSERVATION {k+1}                                                      |", file=f1)
			print(f"|                                                   COMPENSATION {compensation_oc[c]} €                                                   |", file=f1)
			print(f"|                                                                                                                        |", file=f1)
			print(f"|------------------------------------------------------------------------------------------------------------------------|", file=f1)
			print(f"|     |     NEW PACKAGES      |    DELIVERIES    | ACCUMULATED DELIVERIES |            COSTS           |  LOCKER STATUS  |", file=f1)
			print(f"|{'DAY':^5}|{'total':^7}|{'home':^6} |{'lckr':^6} |{'pf':^5}|{'oc':^5}|{'lckr':^6}|{'pf':^7}|{'oc':^7}|{'lckr':^8}|{'pf':^8}|{'oc':^8}|{'cost':^10}|{'home':^8}|{'lckr':^8}|", file=f1)
			print(f"|------------------------------------------------------------------------------------------------------------------------|", file=f1)
			locker_status = {i:0 for i in [1, 2]} # 1-home ; 2-locker
			accumulated_deliveries = {i:0 for i in [1, 2, 3]} # 1-pf ; 2-oc ; 3-lckr
			accumulated_cost = 0
			max_packages_stored = 0


			# simular os dias
			for i in range(days):

				f1, new_packs, locker_status = new_packages(f1, i, locker_status)
				f1, day_deliver = day_deliveries_func(f1, recipient_prob, locker_status, c, compensation_prob, i)

				f1, locker_status, accumulated_deliveries, pf_cost, oc_cost = update_locker(f1, locker_status, day_deliver, accumulated_deliveries, c, compensation_oc, pf_cost_gt10, i, new_packs)
				
				#guardar o valor maximo de packages	
				if max_packages_stored < locker_status[1] + locker_status[2] :
					max_packages_stored = locker_status[1] + locker_status[2]

				accumulated_cost += pf_cost + oc_cost
		

				print(f"{accumulated_cost:^9.2f}|", file=f1, end = " ") #accumulated cost
				print(f"{locker_status[1]:^7}|{locker_status[2]:^8}|", file=f1) #status hopme sattsu locker
				#print(f"-------------------------------------\n", file=f1)
			
			print(f"|------------------------------------------------------------------------------------------------------------------------|\n\n", file=f1)
			# save results from k observation	
			data_cost[k] = accumulated_cost
			data_packages[k] = max_packages_stored
			#print(f"observacao {k+1} compensacao {compensation_oc[c]} | pacotes maximos: {max_packages_stored}")

		# analise estatistica para o custo total
		val_cost[c][0], val_cost[c][1] = mean_confidence_interval(data_cost, alpha)

		# analise estatistica para o maximo de packages guardados no cacifo
		val_packs[c][0], val_packs[c][1] = mean_confidence_interval(data_packages, alpha)
		val_packs[c][0] = round(val_packs[c][0])
		val_packs[c][1] = round(val_packs[c][1])

		# imprimir resultados obtidos
		print(f"|{compensation_oc[c]:^15}€ |{val_cost[c][0]:^20.2f}|{val_cost[c][1]:^20.2f}|{int(val_packs[c][0]):^20}|{int(val_packs[c][1]):^20}|", file=f2)
	print(f"|-----------------------------------------------------------------------------------------------------|", file=f2)

	print(f"\n\t\t--- %s seconds ---" % (time.time() - start_time), file=f2)	
	
	f1.close()
	f2.close()

	return 



if __name__ == "__main__":
	print("A CALCULAR A SIMULAÇÃO ...")
	simulation()
	print("SIMULAÇÃO PRONTA!")