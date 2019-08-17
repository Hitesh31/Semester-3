note
	description: "INVERSEMATRIX application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS_32

create
	make
feature {NONE} -- Initialization
	num,bo: INTEGER --matrix size
	n:REAL
	arr: ARRAY2[REAL] --matrix
	inverse: ARRAY2[REAL] --inverse matrix if exists
	answer:BOOLEAN	--flag that tells determinant is zero or not
	make
		require
			true
		local
			i,j:INTEGER
		do
			input(bo)
			create arr.make_filled(0,num,num) --initialise matrix of size n,n (1st parameter is no.of rows,2nd is no. of columns)
			create inverse.make_filled(0,num,num)
			create_matrix(num,arr) --function to create matrix
			answer:=inversematrix(num,arr,inverse)	--result value of determinant
			if
				answer=false --if false inverse doesn't exist
			then
				print("INVALID%N")
			else	--if exists
					from
						i:=1
					invariant
						i>=1 and i<=num+1
					until
						i > num
					loop
						from
							j:=1
						invariant
							j>=1 and j<=num+1
						until
							j > num
						loop
							print(inverse[i,j])
							print(" ")
							j:=j+1
						end
						print("%N")
						i:=i+1
					end
			end
			rescue
				print("INVALID%N")
				retry
		end
		input(h:INTEGER)
		require
			condition:true
		local u:INTEGER
		do
			Io.read_real
			n:=Io.last_real
			num:=n.truncated_to_integer
			ensure
				this: num>0 and num=n
--			rescue
--				print("INVALID%N")
--				retry
		end
		create_matrix(no:INTEGER;ar:ARRAY2[REAL]) --function that create matrix
		require
			 true and num>0
		local
			i,j:INTEGER
		do
			i:=1
			j:=1
			from
				i:=1
			invariant
				j>=1 and i<=num+1
			until
				i > no
			loop
				from
					j:=1
				invariant
					j>=1 and j<=num+1
				until
					j > no
				loop
					Io.read_real	--take input as real
					ar[i,j]:=Io.last_real	--store in matrix
					j:=j+1
				end
				i:=i+1
			end
			ensure
				that: num>0 and arr.height=num and arr.width=num
			rescue
				print("INVALID%N")
				retry
		end
		swaprow(row:INTEGER;col:INTEGER;ar:ARRAY2[REAL];inv:ARRAY2[REAL]):BOOLEAN
			require
				poll:true and num>0 and arr.height=num and arr.width=num and inverse.height=num and inverse.width=num
			local
				k,l,max:INTEGER
				swap,temp,maximum:REAL
			do
				max:=row
				maximum:=ar[row,col]
				k:=row+1
				from
					k:=row+1
				invariant
					k>=row+1 and k<=num+1
				until
					k>num
				loop
					if
						maximum<ar[k,col] or maximum=0
					then
						if
							ar[k,col]/=0
						then
							max:=k
							maximum:=ar[k,col]
						end
					end
					k:=k+1
				end
				maximum:=ar[max,col]
				if
					maximum=0
				then
					--print("correct%N")
					result:=false
				else
					if
						maximum/=ar[row,col]
					then
						from
							l:=1
						invariant
							l>=1 and l<=num+1
						until
							l>num
						loop
							swap:=ar[max,l]
							ar[max,l]:=ar[row,l]
							ar[row,l]:=swap
							temp:=inv[max,l]
							inv[max,l]:=inv[row,l]
							inv[row,l]:=temp
							l:=l+1
						end
					end
					--print("incorrect%N")
					result:=true
				end
				ensure
					code: arr[row,col]/=0
				--rescue
					--print("INVALID%N")
			end
		inversematrix(no:INTEGER;ar:ARRAY2[REAL];inv:ARRAY2[REAL]):	BOOLEAN
		require
			true and num>0 and arr.height=num and arr.width=num and inverse.height=num and inverse.width=num
		local
			i,j,row,col,k,b,p,q:INTEGER
			res:BOOLEAN
			d:REAL
		do
			from
				i:=1
			invariant
				i>=1 and i<=num+1
			until
				i>no
			loop
				from
					j:=1
				invariant
					j>=1 and j<=num+1
				until
					j>no
				loop
					if
						i=j
					then
						inv[i,j]:=1
					else
						inv[i,j]:=0
					end
					j:=j+1
				end
				i:=i+1
			end

			col:=1
			from
				row:=1
			invariant
				row>=1 and row<=num+1
			until
				row>no
			loop
				res:=swaprow(row,col,ar,inv)
				if
					res=false
				then
					result:=false
					row:=no
					--print("Turned correct%N")
				else
					from
						k:=1
					invariant
						k>=1 and k<=num+1
					until
						k>no
					loop
						if
							k/=row
						then
							d:=ar[k,col]/ar[row,col]
							from
								b:=1
							until
								b>no
							loop
								ar[k,b]:=ar[k,b]-d*ar[row,b]
								inv[k,b]:=inv[k,b]-d*inv[row,b]
								b:=b+1
							end
						end
						k:=k+1
						result:=true
						--print("BIZZARE%N")
					end
				end
				row:=row+1
				col:=col+1
			end
			from
				p:=1
			invariant
				p>=1 and p<=num+1
			until
				p>no
			loop
				from
					q:=1
				invariant
					q>=1 and q<=num+1
				until
					q>no
				loop
					inv[p,q]:=inv[p,q]/ar[p,p]
					q:=q+1
				end
				p:=p+1
			end
		end
end
